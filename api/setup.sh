#!/bin/bash
rm -fr files
rm -f frogy.db
mkdir files
touch frogy.db
cat migrations/user.sql | sqlite3 frogy.db