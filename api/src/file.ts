import multer from "multer";
import * as fs from "fs";
import Controller from "./controller.ts";
import { Request, Response, Router } from "express";

const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, "files/");
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname);
  },
});

const upload = multer({ storage: storage });

class FileController implements Controller {
  static path = "/file";
  router: Router;

  constructor() {
    this.router = Router();
    this.router.get(
      FileController.path,
      this.getListFiles,
    );
    this.router.post(
      FileController.path,
      upload.single("file"),
      this.uploadFiles,
    );
  }

  uploadFiles(req: Request, res: Response) {
    console.log("[INFO][POST] new file added :");
    console.log(req.file);
    res.json({ message: "Successfully uploaded files" });
  }

  getListFiles(req: Request, res: Response) {
    const directoryPath = "files/";

    fs.readdir(directoryPath, function (err, files) {
      if (err) {
        res.status(500).send({
          message: "Unable to scan files!",
        });
      }

      let fileInfos = [];

      files.forEach((file) => {
        fileInfos.push({
          name: file,
        });
      });

      console.log("[INFO][GET] list of files");
      res.status(200).send(fileInfos);
    });
  }

  download(req, res) {
    const fileName = req.params.name;
    const directoryPath = "files/";

    res.download(directoryPath + fileName, fileName, (err) => {

      console.log("[INFO][GET] file : "+fileName);
      if (err) {
        res.status(500).send({
          message: "Could not download the file. " + err,
        });
      }
    });
  }
}

export default FileController;