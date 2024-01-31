# Student Database - Frontend

Frontend for the Student Database application

-  Available at [Student Database](https://c276-studentdatabase.onrender.com/)

## Student Display

Each student is displayed on the main screen within their own respective _cards_
and are displayed through triangles that follow the following design principle:

-  Top corner represents student _age_
-  Left corner represents student _height_
-  Right corner represents student _weight_

## Site Workflow

The site has a main interaction bar at the top with the following options:

<img src="./assets/buttonBar.png"  width="400">

The main display area directly below:

<img src="./assets/mainDisplay.png"  width="400">

To update, view, and add a student the user gets shown one of these:

<img src="./assets/updateStudent.png"  width="200">
<img src="./assets/viewStudent.png"  width="210">
<img src="./assets/addStudent.png"  width="220">

To delete a student the user gets shown this on click:

<img src="./assets/deleteStudent.png"  width="200">

In the case of an input error, the user gets shows this:

## <img src="./assets/error.png"  width="200">

## Info

-  When running localhost, utilize port 8080 -> http://localhost:8080/
-  `backend` folder consists of spring backend, this is the deployed product
-  `frontend` folder consists of the raw svelte frontend

## Tools Utilized

-  Used [svelte](https://svelte.dev/) to create a reactive webpage
-  Utilized Java Spring in the backend to create endpoints and interact with database
-  Used a PostgreSQL database to store all student data
