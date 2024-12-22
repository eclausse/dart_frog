import Controller from "./controller.ts";
import { Request, Response, Router } from "express";
import { Database } from "sqlite3";
import { log } from "console";

class TaskController implements Controller {
  static path = "/task";
  router: Router;

  constructor() {
    this.router = Router();
    this.router.get(TaskController.path, this.get);
    this.router.post(TaskController.path + "/add", this.post);
    this.router.post(TaskController.path + "/anyforme", this.get_by_id);
  }

  static get_values() {
    const db = new Database("frogy.db");
    const sql = "SELECT rowid, * FROM task";

    return new Promise((resolve, reject) =>
      db.all(sql, [], (err, rows) => {
        if (err) {
          console.log(err);
        }
        resolve(rows);
      })
    );
  }


  async get(_req: Request, res: Response) {
    let tasks: TaskEntry[] = [];

    await TaskController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        tasks.push(new TaskEntry(row.id, row.uid, row.name));
      })
    );

    console.log(
      "[INFO][GET] get alls on " + TaskController.path,
    );
    res.send(JSON.stringify(tasks));
  }

  async get_by_id(req: Request, res: Response) {
    const uid = req.body.uid;

    let r: TaskImplant[] = [];

    if (!uid) {
      console.log(
        "[ERROR][POST] wrong data on " + TaskController.path + "/anyforme : " +
          JSON.stringify(req.body),
      );
      res.status(400).send();
      return;
    }

    await TaskController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        if (row.uid == uid) {
          r.push(new TaskImplant(row.uid, row.name));
        }
      })
    );

    const db = new Database("frogy.db");
    const sql = `DELETE FROM task
    WHERE uid = ?`;
    const data = uid;

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + TaskController.path + "/anyforme : " +
          JSON.stringify(uid),
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
    "[INFO][POST] " + TaskController.path + "/anyforme " + uid,
    );
    console.log(r);
    res.send(JSON.stringify(r));
  }


  async post(req: Request, res: Response) {
    const name = req.body.name;
    const uid = req.body.uid

    if (!uid || !name) {
      console.log(
        "[ERROR][POST] wrong data on " + TaskController.path + " : " +
          JSON.stringify(req.body),
      );
      res.status(400).send();
      return;
    }

    let sql = "INSERT INTO task VALUES(?, ?)";
    let data = [
        uid,
        name,
    ];
    const db = new Database("frogy.db");

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + TaskController.path + " : " 
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][POST] data added on " + TaskController.path + " : " +
        JSON.stringify(name),
    );
    res.status(200).send();
  }

  
  async delete(req: Request, res: Response) {
    const db = new Database("frogy.db");
    const { id } = req.body;

    if (
      !id
    ) {
      console.log(
        "[ERROR][DELETE] wrong data on " + TaskController.path + " : " +
          JSON.stringify(req.body),
      );
    }

    const sql = `DELETE FROM task
    WHERE name = ?`;
    const data = [id];

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + TaskController.path + " : " +
          JSON.stringify(id),
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][DELETE] data deleted on " + TaskController.path + " : " +
        JSON.stringify(id),
    );
    res.status(200).send();
  }
}

export default TaskController;

class TaskImplant {
    uid: string;
  name: string;
  constructor(
    uid: string,
    name: string
  ) {
    this.uid = uid;
    this.name = name;
  }
}

class TaskEntry {
  id: string;
  uid: string;
  name: string;

  constructor(
    id: string,
    uid: string, 
    name: string,
  ) {
    this.id = id;
    this.uid = uid;
    this.name = name;
  }
}