#!/bin/bash
rm -fr files
rm -f frogy.db
mkdir files
touch frogy.db
cat migrations/user.sql | sqlite3 frogy.db
cat migrations/result.sql | sqlite3 frogy.db
cat migrations/task.sql | sqlite3 frogy.db