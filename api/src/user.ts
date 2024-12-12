import Controller from "./controller.ts";
import { Request, Response, Router } from "express";
import { Database } from "sqlite3";
import { log } from "console";

class UserController implements Controller {
  static path = "/user";
  router: Router;

  constructor() {
    this.router = new Router();
    this.router.get(UserController.path, this.get);
    this.router.post(UserController.path + "/register", this.post);
  }

  static get_values() {
    const db = new Database("frogy.db");
    const sql = "SELECT rowid, * FROM user";

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
    let users: String[] = [];

    await UserController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        users.push(row.name);
      })
    );

    console.log(
      "[INFO][GET] get alls on " + UserController.path,
    );
    res.send(JSON.stringify(users));
  }


  async post(req: Request, res: Response) {
    const name = req.body.name;

    let users: String[] = [];

    await UserController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        users.push(row.name);
      })
    );

    if (!name || users.includes(name)) {
      console.log(
        "[ERROR][POST] wrong data on " + UserController.path + " : " +
          JSON.stringify(req.body),
      );
      res.status(400).send();
      return;
    }

    let sql = "INSERT INTO user VALUES(?)";
    let data = [
      name,
    ];
    const db = new Database("frogy.db");

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + UserController.path + " : " 
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][POST] data added on " + UserController.path + " : " +
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
        "[ERROR][DELETE] wrong data on " + UserController.path + " : " +
          JSON.stringify(req.body),
      );
    }

    const sql = `DELETE FROM user
    WHERE name = ?`;
    const data = [id];

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + UserController.path + " : " +
          JSON.stringify(id),
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][DELETE] data deleted on " + UserController.path + " : " +
        JSON.stringify(id),
    );
    res.status(200).send();
  }
}

export default UserController;

class User {
  name: string;
  constructor(
    name: string
  ) {
    this.name = name;
  }
}

class UserEntry {
  id: number;
  name: string;

  constructor(
    id: number,
    name: string,
  ) {
    this.id = id;
    this.name = name;
  }
}