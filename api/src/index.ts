import App from "./app";
import UserController from "./user";
import ResultController from "./result";
import TaskController from "./task";
import FileController from "./file";

const controllers = [
  new UserController(),
  new ResultController(),
  new TaskController(),
  new FileController(),
];

const app = new App(
  controllers,
  8080,
);

app.listen();