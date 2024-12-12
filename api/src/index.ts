import App from "./app";
import UserController from "./user";

const controllers = [
  new UserController(),
];

const app = new App(
  controllers,
  8080,
);

app.listen();