var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(mod)) : {}, __copyProps(
  // If the importer is in node compatibility mode or this is not an ESM
  // file that has been converted to a CommonJS file using a Babel-
  // compatible transform (i.e. "__esModule" has not been set), then set
  // "default" to the CommonJS "module.exports" for node compatibility.
  isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod, enumerable: true }) : target,
  mod
));

// src/app.ts
var import_cors = __toESM(require("cors"));
var import_express = __toESM(require("express"));
var bodyParser = __toESM(require("body-parser"));
var App = class {
  constructor(controllers2, port) {
    this.app = (0, import_express.default)();
    this.port = port;
    this.controllers = controllers2;
    this.app.get("/ping", (_req, res) => res.send("PONG !"));
    this.initializeMiddlewares();
    this.initializeControllers(this.controllers);
  }
  initializeMiddlewares() {
    this.app.use((0, import_cors.default)());
    this.app.use(bodyParser.json());
    this.app.use(bodyParser.urlencoded({ extended: true }));
    this.app.use("/files", import_express.default.static("files"));
  }
  initializeControllers(controllers2) {
    controllers2.forEach((controller) => {
      this.app.use("/api", controller.router);
    });
  }
  listen() {
    this.app.listen(this.port, () => {
      console.log(`[INFO] Frogy Api started on port ${this.port}`);
      this.app.use("/", import_express.default.static("../front/dist/"));
      this.app.get("*", function(_req, res) {
        res.redirect("/");
      });
    });
  }
};
var app_default = App;

// src/user.ts
var import_express2 = require("express");
var import_sqlite3 = require("sqlite3");
var _UserController = class {
  constructor() {
    this.router = new import_express2.Router();
    this.router.get(_UserController.path, this.get);
    this.router.post(_UserController.path + "/register", this.post);
  }
  static get_values() {
    const db = new import_sqlite3.Database("frogy.db");
    const sql = "SELECT rowid, * FROM user";
    return new Promise(
      (resolve, reject) => db.all(sql, [], (err, rows) => {
        if (err) {
          console.log(err);
        }
        resolve(rows);
      })
    );
  }
  async get(_req, res) {
    let users = [];
    await _UserController.get_values().then(
      (rows) => rows.forEach((row) => {
        users.push(row.name);
      })
    );
    console.log(
      "[INFO][GET] get alls on " + _UserController.path
    );
    res.send(JSON.stringify(users));
  }
  async post(req, res) {
    const uid = req.body.uid;
    const name = req.body.name;
    let users = [];
    await _UserController.get_values().then(
      (rows) => rows.forEach((row) => {
        users.push(new UserEntry(row.id, row.uid, row.name));
      })
    );
    if (!name || users.includes(name) || !uid || users.includes(uid)) {
      console.log(
        "[ERROR][POST] wrong data on " + _UserController.path + " : " + JSON.stringify(req.body)
      );
      res.status(400).send();
      return;
    }
    let sql = "INSERT INTO user VALUES(?, ?)";
    let data = [
      uid,
      name
    ];
    const db = new import_sqlite3.Database("frogy.db");
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + _UserController.path + " : "
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][POST] data added on " + _UserController.path + " : " + JSON.stringify(name)
    );
    res.status(200).send();
  }
  async delete(req, res) {
    const db = new import_sqlite3.Database("frogy.db");
    const { id } = req.body;
    if (!id) {
      console.log(
        "[ERROR][DELETE] wrong data on " + _UserController.path + " : " + JSON.stringify(req.body)
      );
    }
    const sql = `DELETE FROM user
    WHERE name = ?`;
    const data = [id];
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + _UserController.path + " : " + JSON.stringify(id)
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][DELETE] data deleted on " + _UserController.path + " : " + JSON.stringify(id)
    );
    res.status(200).send();
  }
};
var UserController = _UserController;
UserController.path = "/user";
var user_default = UserController;
var UserEntry = class {
  constructor(id, uid, name) {
    this.id = id;
    this.uid = uid;
    this.name = name;
  }
};

// src/result.ts
var import_express3 = require("express");
var import_sqlite32 = require("sqlite3");
var _ResultController = class {
  constructor() {
    this.router = new import_express3.Router();
    this.router.get(_ResultController.path, this.get);
    this.router.post(_ResultController.path + "/add", this.post);
  }
  static get_values() {
    const db = new import_sqlite32.Database("frogy.db");
    const sql = "SELECT rowid, * FROM result";
    return new Promise(
      (resolve, reject) => db.all(sql, [], (err, rows) => {
        if (err) {
          console.log(err);
        }
        resolve(rows);
      })
    );
  }
  async get(_req, res) {
    let results = [];
    await _ResultController.get_values().then(
      (rows) => rows.forEach((row) => {
        results.push(new ResultEntry(row.id, row.uid, row.content, row.code));
      })
    );
    console.log(
      "[INFO][GET] get alls on " + _ResultController.path
    );
    res.send(JSON.stringify(results));
  }
  async post(req, res) {
    const uid = req.body.uid;
    const content = req.body.content;
    const code = req.body.code;
    let results = [];
    if (!uid || !content || !code) {
      console.log(
        "[ERROR][POST] wrong data on " + _ResultController.path + "/add : " + JSON.stringify(req.body)
      );
      res.status(400).send();
      return;
    }
    let sql = "INSERT INTO result VALUES(?, ?, ?)";
    let data = [
      uid,
      content,
      code
    ];
    const db = new import_sqlite32.Database("frogy.db");
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + _ResultController.path + " : "
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][POST] data added on " + _ResultController.path + " : " + JSON.stringify(uid, content, code)
    );
    res.status(200).send();
  }
  async delete(req, res) {
    const db = new import_sqlite32.Database("frogy.db");
    const { id } = req.body;
    if (!id) {
      console.log(
        "[ERROR][DELETE] wrong data on " + _ResultController.path + " : " + JSON.stringify(req.body)
      );
    }
    const sql = `DELETE FROM result
    WHERE name = ?`;
    const data = [id];
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + _ResultController.path + " : " + JSON.stringify(id)
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][DELETE] data deleted on " + _ResultController.path + " : " + JSON.stringify(id)
    );
    res.status(200).send();
  }
};
var ResultController = _ResultController;
ResultController.path = "/result";
var result_default = ResultController;
var ResultEntry = class {
  constructor(id, uid, content, code) {
    this.id = id;
    this.uid = uid;
    this.content = content;
    this.code = code;
  }
};

// src/task.ts
var import_express4 = require("express");
var import_sqlite33 = require("sqlite3");
var _TaskController = class {
  constructor() {
    this.router = new import_express4.Router();
    this.router.get(_TaskController.path, this.get);
    this.router.post(_TaskController.path + "/add", this.post);
    this.router.post(_TaskController.path + "/anyforme", this.get_by_id);
  }
  static get_values() {
    const db = new import_sqlite33.Database("frogy.db");
    const sql = "SELECT rowid, * FROM task";
    return new Promise(
      (resolve, reject) => db.all(sql, [], (err, rows) => {
        if (err) {
          console.log(err);
        }
        resolve(rows);
      })
    );
  }
  async get(_req, res) {
    let tasks = [];
    await _TaskController.get_values().then(
      (rows) => rows.forEach((row) => {
        tasks.push(new TaskEntry(row.id, row.uid, row.name));
      })
    );
    console.log(
      "[INFO][GET] get alls on " + _TaskController.path
    );
    res.send(JSON.stringify(tasks));
  }
  async get_by_id(req, res) {
    const uid = req.body.uid;
    const name = req.body.uid;
    let r = [];
    if (!uid || !name) {
      console.log(
        "[ERROR][POST] wrong data on " + _TaskController.path + "/anyforme : " + JSON.stringify(req.body)
      );
      res.status(400).send();
      return;
    }
    await _TaskController.get_values().then(
      (rows) => rows.forEach((row) => {
        if (row.uid == uid) {
          r.push(new TaskImplant(row.uid, row.name));
        }
      })
    );
    console.log(
      "[INFO][POST] " + _TaskController.path + "/anyforme " + uid
    );
    console.log(r);
    res.send(JSON.stringify(r));
  }
  async post(req, res) {
    const name = req.body.name;
    const uid = req.body.uid;
    if (!uid || !name) {
      console.log(
        "[ERROR][POST] wrong data on " + _TaskController.path + " : " + JSON.stringify(req.body)
      );
      res.status(400).send();
      return;
    }
    let sql = "INSERT INTO task VALUES(?, ?)";
    let data = [
      uid,
      name
    ];
    const db = new import_sqlite33.Database("frogy.db");
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + _TaskController.path + " : "
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][POST] data added on " + _TaskController.path + " : " + JSON.stringify(name)
    );
    res.status(200).send();
  }
  async delete(req, res) {
    const db = new import_sqlite33.Database("frogy.db");
    const { id } = req.body;
    if (!id) {
      console.log(
        "[ERROR][DELETE] wrong data on " + _TaskController.path + " : " + JSON.stringify(req.body)
      );
    }
    const sql = `DELETE FROM task
    WHERE name = ?`;
    const data = [id];
    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + _TaskController.path + " : " + JSON.stringify(id)
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();
    console.log(
      "[INFO][DELETE] data deleted on " + _TaskController.path + " : " + JSON.stringify(id)
    );
    res.status(200).send();
  }
};
var TaskController = _TaskController;
TaskController.path = "/task";
var task_default = TaskController;
var TaskImplant = class {
  constructor(uid, name) {
    this.uid = uid;
    this.name = name;
  }
};
var TaskEntry = class {
  constructor(id, uid, name) {
    this.id = id;
    this.uid = uid;
    this.name = name;
  }
};

// src/index.ts
var controllers = [
  new user_default(),
  new result_default(),
  new task_default()
];
var app = new app_default(
  controllers,
  8080
);
app.listen();
