<script>
   import ViewStudent from "./lib/ViewStudent.svelte";
   import ViewModal from "./lib/ViewModal.svelte";
   import UpdateModal from "./lib/UpdateModal.svelte";
   import DeleteModal from "./lib/DeleteModal.svelte";
   import AddModal from "./lib/AddModal.svelte";
   import ErrorModal from "./lib/ErrorModal.svelte";
   import { afterUpdate, onMount } from "svelte";

   let students = [];
   let singleStudent, newStudent;
   let viewOne = false,
      deleteOne = false,
      updateOne = false,
      addOne = false;

   let viewInput, updateInput, deleteInput;

   let showError = false;

   // get all students
   async function fetchAllStudents() {
      // "http://localhost:8080/students/view"
      // "/students/view"
      fetch("/students/view", {
         method: "GET",
      })
         .then((response) => response.json())
         .then((data) => {
            students = data; // assign retrieved JSON data
         })
         .catch((error) => {
            console.log("===== ERROR =====");
            console.log(error);
         });
   }

   // get one student
   function fetchStudentByUid() {
      viewOne = true;
      updateOne = false;
      deleteOne = false;
      addOne = false;
      showError = false;
      getStudent(viewInput);
   }

   async function getStudent(desiredId) {
      singleStudent = null;
      // `http://localhost:8080/students/view/${desiredId}`
      // `/students/view/${desiredId}`
      fetch(`/students/view/${desiredId}`, {
         method: "GET",
      })
         .then((response) => response.json())
         .then((data) => {
            singleStudent = data; // assign retrieved JSON data
         })
         .catch((error) => {
            console.log("===== ERROR =====");
            console.log(error);
         });
   }

   // Add one student
   function addStudentPrompt() {
      addOne = true;
      deleteOne = false;
      viewOne = false;
      updateOne = false;
      showError = false;
   }
   // create add student endpoint request
   async function addStudentRequest() {
      console.log(newStudent); //new student details
      // "http://localhost:8080/students/add"
      // "/students/add"
      fetch("/students/add", {
         method: "POST",
         headers: {
            "Content-Type": "application/json",
         },
         body: JSON.stringify(newStudent),
      })
         .then((response) => {
            if (response.status === 201 || response.status === 200) {
               // Update was successful
               fetchAllStudents(); // Refresh the student list
            } else if (response.status === 400) {
               // Bad request
               console.log("Invalid uid");
            }
         })
         .catch((error) => {
            console.log("===== ERROR =====");
            console.log(error);
         });
   }

   // Update one student
   function updateStudentByUid() {
      updateOne = true;
      viewOne = false;
      deleteOne = false;
      addOne = false;
      showError = false;
      // Getting student data
      getStudent(updateInput);
   }

   async function updateStudentRequest() {
      console.log(newStudent); //update details
      // `http://localhost:8080/students/update/${updateInput}`
      // `/students/update/${updateInput}`
      fetch(`/students/update/${updateInput}`, {
         method: "PUT",
         headers: {
            "Content-Type": "application/json",
         },
         body: JSON.stringify(newStudent),
      })
         .then((response) => {
            if (response.status === 201 || response.status === 200) {
               // Update was successful
               fetchAllStudents(); // Refresh the student list
            } else if (response.status === 400) {
               // Bad request
               console.log("Invalid uid");
            }
         })
         .catch((error) => {
            console.log("===== ERROR =====");
            console.log(error);
         });
   }

   // Delete one student
   function deleteStudentByUid() {
      deleteOne = true;
      viewOne = false;
      updateOne = false;
      addOne = false;
      showError = false;
      // Getting student data
      getStudent(deleteInput);
   }

   async function deleteStudent() {
      // `http://localhost:8080/students/delete/${deleteInput}`
      // `/students/delete/${deleteInput}`
      fetch(`/students/delete/${deleteInput}`, {
         method: "DELETE",
      })
         .then((response) => {
            if (response.status === 201 || response.status === 200) {
               // delete was successful
               fetchAllStudents(); // Refresh the student list
            } else if (response.status === 400) {
               // Bad request
               console.log("Invalid uid");
            }
         })
         .catch((error) => {
            console.log("===== ERROR =====");
            console.log(error);
         });
   }

   // Modal controls
   function toggleView() {
      viewOne = !viewOne;
   }
   function toggleUpdate() {
      updateOne = !updateOne;
   }
   function toggleDelete() {
      deleteOne = !deleteOne;
   }
   function toggleAdd() {
      addOne = !addOne;
   }

   // Event dispatch handlers
   function handleVisualMounted(event) {
      console.log(`Visual with ID ${event.detail} has been mounted.`);
   }

   function receiveUpdatedStudentData(event) {
      newStudent = event.detail;
   }

   function receiveNewStudentData(event) {
      newStudent = event.detail;
   }

   // uId input validation
   function uidValidation() {
      let viewValue = parseInt(viewInput);
      let updateValue = parseInt(updateInput);
      let deleteValue = parseInt(deleteInput);
      if (viewValue < 0 || updateValue < 0 || deleteValue < 0) {
         viewInput = "";
         updateInput = "";
         deleteInput = "";
         displayErrorModal();
      }
   }

   // Error Handling
   function toggleError() {
      showError = false;
   }

   function displayErrorModal() {
      showError = true;
      setTimeout(() => {
         toggleError();
      }, 2500);
   }

   // updates all students when DOM renders components (ie. refresh)
   onMount(() => {
      fetchAllStudents();
   });
</script>

<h1>Student Database</h1>
<main
   class="p-3 {viewOne ? 'inactive' : ''} {deleteOne ? 'inactive' : ''} 
   {updateOne ? 'inactive' : ''} {addOne ? 'inactive' : ''} {showError ? 'inactive' : ''}"
>
   <!-- Buttons -->
   <form id="buttons">
      <div>
         <button on:click={addStudentPrompt} type="button" class="btn btn-primary">
            Add Student
         </button>
      </div>
      <div class="input-group col-sm">
         <button
            on:click={fetchStudentByUid}
            type="button"
            class="btn btn-primary"
            disabled={!viewInput}
         >
            View
         </button>
         <input
            bind:value={viewInput}
            on:input={uidValidation}
            type="number"
            class="form-control"
            placeholder="uid"
         />
      </div>
      <div class="input-group col-sm">
         <button
            on:click={updateStudentByUid}
            type="button"
            class="btn btn-primary"
            disabled={!updateInput}
         >
            Update
         </button>
         <input
            type="number"
            class="form-control"
            placeholder="uid"
            bind:value={updateInput}
            on:input={uidValidation}
         />
      </div>
      <div class="input-group col-sm">
         <button
            on:click={deleteStudentByUid}
            type="button"
            class="btn btn-primary"
            disabled={!deleteInput}
         >
            Delete
         </button>
         <input
            type="number"
            class="form-control"
            placeholder="uid"
            bind:value={deleteInput}
            on:input={uidValidation}
         />
      </div>
   </form>
   <!-- Displaying All Students -->
   <div class="container-fluid p-3 gap-3" id="displayArea">
      {#each students as std}
         <div class="card text-white bg-secondary" style="width: 23rem;">
            <div class="card-body">
               <h4 class="card-title">{std.name}</h4>
               <p class="card-subtitle mb-2 text-white-50">uID: {std.uid}</p>
               <p class="card-text px-3">
                  <ViewStudent
                     age={std.age}
                     hairColor={std.hairColor}
                     weight={std.weight}
                     height={std.height}
                     on:visualMounted={handleVisualMounted}
                  />
               </p>
            </div>
         </div>
      {/each}
   </div>
</main>

{#if viewOne}
   <ViewModal uid={viewInput} {...singleStudent} {toggleView} />
{:else if updateOne}
   <UpdateModal
      uid={updateInput}
      {...singleStudent}
      {toggleUpdate}
      updateStudent={updateStudentRequest}
      on:newStudentData={receiveUpdatedStudentData}
   />
{:else if addOne}
   <AddModal {toggleAdd} addStudent={addStudentRequest} on:newStudentData={receiveNewStudentData} />
{:else if deleteOne}
   <DeleteModal uid={deleteInput} deletingStudent={singleStudent} {toggleDelete} {deleteStudent} />
{:else if showError}
   <ErrorModal {toggleError} />
{/if}

<style>
   main {
      z-index: 1;
   }

   .inactive {
      filter: blur(10px);
      pointer-events: none;
   }
</style>
