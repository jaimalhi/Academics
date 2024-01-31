<script>
   import ViewStudent from "./ViewStudent.svelte";

   export let toggleView;

   export let name;
   export let uid;
   export let age;
   export let gpa;
   export let hairColor;
   export let weight;
   export let height;

   function handleClick() {
      toggleView();
   }

   function handleVisualMounted(event) {
      console.log(`Visual with ID ${event.detail} has been mounted.`);
   }
</script>

<!-- Modal -->
<div class="showModal">
   <div class="card text-center text-white bg-secondary" style="width: 30rem;">
      {#if name == null}
         <h3 class="card-header">Not Found</h3>
         <div class="card-body">
            <p>Could not find a student with uId: {uid}</p>
         </div>
         <button class="btn btn-primary" on:click={handleClick}><strong>Close</strong></button>
      {:else}
         <h3 class="card-header">{name}</h3>
         <div class="card-body">
            <h5 class="card-title text-white-50">uID: {uid}</h5>
            <p class="card-text">
               <ViewStudent
                  {age}
                  {hairColor}
                  {weight}
                  {height}
                  on:visualMounted={handleVisualMounted}
               />
            </p>
            <ul class="list-group list-group-flush">
               <li class="list-group-item"><strong>Age:</strong> {age}</li>
               <li class="list-group-item"><strong>Height:</strong> {height}</li>
               <li class="list-group-item"><strong>Weight:</strong> {weight}</li>
               <li class="list-group-item"><strong>GPA:</strong> {gpa}</li>
               <li class="list-group-item"><strong>Hair:</strong> {hairColor}</li>
            </ul>
         </div>
         <button class="btn btn-primary" on:click={handleClick}><strong>Close</strong></button>
      {/if}
   </div>
</div>

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

   button {
      border-top-left-radius: 0;
      border-top-right-radius: 0;
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

   .list-group {
      border-radius: 15px;
   }

   .card-text {
      margin-left: 5rem;
   }
</style>
