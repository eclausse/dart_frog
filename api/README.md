# Paths

- GET /ping respond "Pong !"

## Users

- GET /api/user to get all the registered devices

- POST /api/user/register to add a new device REQUIRE BODY: uid, name

## Tasks

- GET /api/task to get all tasks

- POST /api/task/add to add a new task REQUIRES BODY: uid, name

- POST /api/task/anyforme to get all tasks from a uid REQUIRES BODY: uid

## Results

- GET /api/result to get all the results

- POST /api/result/add to add a new result REQUIRES BODY: uid, content, code