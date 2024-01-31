<script>
   export let toggleError;

   function handleClick() {
      toggleError();
   }
</script>

<!-- Modal -->
<div class="showModal">
   <div class="card text-center text-white bg-secondary" style="width: 35rem; height: auto;">
      <h3 class="card-header">An Error Occured</h3>
      <div class="card-body">
         <p class="card-text">Please double-check input and try again</p>
      </div>
      <button class="btn btn-primary" on:click={handleClick}><strong>Close</strong></button>
   </div>
</div>

<style>
   .showModal {
      position: absolute;
      top: 25%;
      left: 50%;
      transform: translate(-50%, -50%);
      z-index: 5;

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
      box-shadow: rgba(252, 0, 0, 0.5) 0px 5px 20px;
   }
</style>
