import App from "./app";
import UserController from "./user";
import ResultController from "./result";
import TaskController from "./task";

const controllers = [
  new UserController(),
  new ResultController(),
  new TaskController(),
];

const app = new App(
  controllers,
  8080,
);

app.listen();