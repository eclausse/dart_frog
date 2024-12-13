import Controller from "./controller.ts";
import { Request, Response, Router } from "express";
import { Database } from "sqlite3";
import { log } from "console";

class ResultController implements Controller {
  static path = "/result";
  router: Router;

  constructor() {
    this.router = new Router();
    this.router.get(ResultController.path, this.get);
    this.router.post(ResultController.path + "/add", this.post);
  }

  static get_values() {
    const db = new Database("frogy.db");
    const sql = "SELECT rowid, * FROM result";

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
    let results: ResultEntry[] = [];

    await ResultController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        results.push(new ResultEntry(row.id, row.uid, row.content, row.code));
      })
    );

    console.log(
      "[INFO][GET] get alls on " + ResultController.path,
    );
    res.send(JSON.stringify(results));
  }


  async post(req: Request, res: Response) {
    const uid = req.body.uid;
    const content = req.body.content;
    const code = req.body.code;

    let results: String[] = [];

    /*
    await UserController.get_values().then((rows: any) =>
      rows.forEach((row) => {
        results.push(row.name);
      })
    );
    */

    if (!uid || !content || !code) {
      console.log(
        "[ERROR][POST] wrong data on " + ResultController.path + "/add : " +
          JSON.stringify(req.body),
      );
      res.status(400).send();
      return;
    }

    let sql = "INSERT INTO result VALUES(?, ?, ?)";
    let data = [
      uid, content, code
    ];
    const db = new Database("frogy.db");

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][POST] sql error " + ResultController.path + " : " 
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][POST] data added on " + ResultController.path + " : " +
        JSON.stringify(uid, content, code),
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
        "[ERROR][DELETE] wrong data on " + ResultController.path + " : " +
          JSON.stringify(req.body),
      );
    }

    const sql = `DELETE FROM result
    WHERE name = ?`;
    const data = [id];

    let e;
    db.run(sql, data, (err) => e = err);
    if (e) {
      console.log(
        "[ERROR][DELETE] sql error " + ResultController.path + " : " +
          JSON.stringify(id),
      );
      console.error(e.message);
      res.status(500).send();
      return;
    }
    db.close();

    console.log(
      "[INFO][DELETE] data deleted on " + ResultController.path + " : " +
        JSON.stringify(id),
    );
    res.status(200).send();
  }
}

export default ResultController;

class Result {
  uid: string;
  content: string;
  code: any;
  constructor(
    uid: string,
    content: string,
    code: any
  ) {
    this.uid = uid;
    this.content = content;
    this.code = code;
  }
}

class ResultEntry {
  id: number;
  uid: string;
  content: string;
  code: any;

  constructor(
    id: number,
    uid: string,
    content: string,
    code: any
  ) {
    this.id = id;
    this.uid = uid;
    this.content = content;
    this.code = code;
  }
}