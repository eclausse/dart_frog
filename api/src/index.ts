import App from "./app";
import UserController from "./user";
import ResultController from "./result";

const controllers = [
  new UserController(),
  new ResultController(),
];

const app = new App(
  controllers,
  8080,
);

app.listen();