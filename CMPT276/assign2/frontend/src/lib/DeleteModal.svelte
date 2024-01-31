<script>
   export let uid;
   export let deletingStudent;
   export let toggleDelete;
   export let deleteStudent;

   function handleClick() {
      toggleDelete();
   }

   function confirmDelete() {
      toggleDelete();
      deleteStudent();
   }
</script>

<!-- Modal -->
<div class="showModal">
   <div class="card text-center text-white bg-secondary" style="width: 30rem; height: auto;">
      {#if deletingStudent == null}
         <h3 class="card-header">Not Found</h3>
         <div class="card-body">
            <p>Could not find a student with uId: {uid}</p>
         </div>
         <button class="btn btn-primary" on:click={handleClick}><strong>Close</strong></button>
      {:else}
         <h3 class="card-header">Deleting Student</h3>
         <div class="card-body">
            <p class="card-text">
               Are you sure you want to delete {deletingStudent.name} with uID: {uid}?
            </p>
            <div class="buttons">
               <button class="btn btn-primary mx-3" style="width: 11rem;" on:click={handleClick}
                  ><strong>Cancel</strong></button
               >
               <button class="btn btn-danger mx-3" style="width: 11rem;" on:click={confirmDelete}
                  ><strong>Delete</strong></button
               >
            </div>
         </div>
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
