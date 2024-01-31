<script>
   import { createEventDispatcher } from "svelte";
   import ErrorModal from "./ErrorModal.svelte";

   const dispatch = createEventDispatcher();

   export let toggleAdd;
   export let addStudent;

   let name;
   let age;
   let gpa;
   let weight;
   let height;
   let hairColor;

   let showError = false;

   function sendStudentData() {
      const newStudent = {
         name: name,
         age: age,
         gpa: gpa,
         weight: weight,
         height: height,
         hairColor: hairColor,
      };
      dispatch("newStudentData", newStudent);
   }

   function handleClick() {
      toggleAdd();
   }

   function confirmAdd() {
      toggleAdd();
      sendStudentData();
      addStudent();
   }

   // Age input validation
   function ageValidate() {
      let value = parseInt(age);
      if (value < 0 || value > 200) {
         age = "";
         displayErrorModal();
      }
   }

   // GPA input validation
   function gpaValidate() {
      let value = parseFloat(gpa);
      // Restrict the input to the range of 0.0 to 10.0
      if (value < 0.0 || value > 10.0) {
         gpa = "";
         displayErrorModal();
      }
   }

   // Height input validation
   function heightValidate() {
      let value = parseInt(height);
      if (value < 0 || value > 400) {
         height = "";
         displayErrorModal();
      }
   }

   // Weight input validation
   function weightValidate() {
      let value = parseInt(weight);
      if (value < 0 || value > 400) {
         weight = "";
         displayErrorModal();
      }
   }

   // Rouding input numbers
   function validateOnBlur() {
      let gpaValue = parseFloat(gpa);
      let weightValue = parseInt(weight);
      let heightValue = parseInt(height);
      let ageValue = parseInt(age);
      // Format the input to two decimal places when input not in focus
      if (!isNaN(gpaValue)) {
         gpa = gpaValue.toFixed(2);
         weight = weightValue.toFixed(0);
         height = heightValue.toFixed(0);
         age = ageValue.toFixed(0);
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
</script>

<!-- Modal -->
<div class="showModal">
   <div class="card text-center text-white bg-secondary" style="width: 30rem; height: auto;">
      <h3 class="card-header">Adding Student</h3>
      <div class="card-body">
         <div class="input-group mb-3">
            <span class="input-group-text">Name</span>
            <input type="text" class="form-control" placeholder="name" bind:value={name} />
         </div>
         <div class="input-group mb-3">
            <span class="input-group-text">Age</span>
            <input
               type="number"
               class="form-control"
               placeholder="age"
               bind:value={age}
               on:input={ageValidate}
               on:blur={validateOnBlur}
            />
         </div>
         <div class="input-group mb-3">
            <span class="input-group-text">GPA</span>
            <input
               type="number"
               class="form-control"
               placeholder="gpa"
               bind:value={gpa}
               on:input={gpaValidate}
               on:blur={validateOnBlur}
            />
         </div>
         <div class="input-group mb-3">
            <span class="input-group-text">Height</span>
            <input
               type="number"
               class="form-control"
               placeholder="height"
               bind:value={height}
               on:input={heightValidate}
               on:blur={validateOnBlur}
            />
         </div>
         <div class="input-group mb-3">
            <span class="input-group-text">Weight</span>
            <input
               type="number"
               class="form-control"
               placeholder="weight"
               bind:value={weight}
               on:input={weightValidate}
               on:blur={validateOnBlur}
            />
         </div>
         <div class="input-group mb-3">
            <span class="input-group-text">Hair Color</span>
            <input
               type="text"
               class="form-control"
               placeholder="Hair Color"
               bind:value={hairColor}
            />
         </div>
         <div class="buttons">
            <button class="btn btn-danger mx-3" style="width: 11rem;" on:click={handleClick}
               ><strong>Cancel</strong></button
            >
            <button class="btn btn-primary mx-3" style="width: 11rem;" on:click={confirmAdd}
               ><strong>Add</strong></button
            >
         </div>
      </div>
   </div>
</div>

{#if showError}
   <ErrorModal {toggleError} />
{/if}

<style>
   .showModal {
      position: absolute;
      top: 45%;
      left: 50%;
      transform: translate(-50%, -50%);
      z-index: 3;

      animation: fadeInAnimation ease 0.7s;
      animation-iteration-count: 1;
      animation-fill-mode: forwards;
   }

   @keyframes fadeInAnimation {
      0% {
         opacity: 0;
      }
      100% {
         opacity: 1;
      }
   }

   .card {
      width: 20rem;
      margin: 1rem;
      transition: transform 0.5s ease;
      box-shadow: rgba(0, 0, 0, 0.5) 0px 5px 20px;
   }

   .card:hover,
   .card:focus {
      transform: scale(1.03);
      box-shadow: rgba(255, 255, 255, 0.5) 0px 5px 20px;
   }
</style>
