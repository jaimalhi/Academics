# Backend for Recipe App
-  Using **Express**, **PostgreSQL**, & **Docker**

### Running the Server
- Start: `docker compose up --build`
- Stop: `docker compose down`
- Enter database through local machine: `psql -h localhost -U postgres -p 4444`

### Querying Arrays in pSQL
-  https://popsql.com/learn-sql/postgresql/how-to-query-arrays-in-postgresql

### JSON Samples:
```
{
  "time_modified": "2024-02-02T05:22:56.113Z",
  "ingredients": [
    "water",
    "shredded cheese",
    "cream cheese",
    "panko breadcrumbs",
    "milk"
  ],
  "instructions": "ask me to do it",
  "title": "Cheese popper"
}

{
"time_modified": "2024-02-01T10:32:26.371Z",
"ingredients": ["water", "beer", "milk", "juice"],
"instructions": "Have the time of your life and hopefully not die in the process",
"title": "Recipes fo Days"
}
```
