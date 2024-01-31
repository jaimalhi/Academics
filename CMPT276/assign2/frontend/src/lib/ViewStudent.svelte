<script>
   import { onMount, afterUpdate } from "svelte";
   import { createEventDispatcher } from "svelte";
   // this component creates the triangles to visualize students
   // left = height, right = weight, top = age

   export let age;
   export let hairColor;
   export let weight;
   export let height;

   // dispatch allows us to assign IDs to each call of <Visuals />
   // so that every student displays correctly
   const dispatch = createEventDispatcher();

   let visualId;
   let triangleElement;

   function updateTriangleStyles() {
      if (triangleElement) {
         triangleElement.style.borderBottomColor = hairColor;
         if (age >= 100) {
            triangleElement.style.borderBottomWidth = `${age}px`;
         } else {
            triangleElement.style.borderBottomWidth = `${age * 2}px`;
         }

         if (height > 249 && weight > 249) {
            triangleElement.style.borderLeftWidth = `${height / 3}px`;
            triangleElement.style.borderRightWidth = `${weight / 3}px`;
         } else if (height > 249) {
            triangleElement.style.borderLeftWidth = `${height / 3}px`;
         } else if (weight > 249) {
            triangleElement.style.borderRightWidth = `${weight / 3}px`;
         } else {
            triangleElement.style.borderLeftWidth = `${height / 2}px`;
            triangleElement.style.borderRightWidth = `${weight / 2}px`;
         }
      }
   }

   onMount(() => {
      visualId = Math.random().toString(36).substring(7);
      updateTriangleStyles();
   });

   afterUpdate(() => {
      updateTriangleStyles();
   });

   dispatch("visualMounted", visualId);
</script>

<div class="container">
   <div class="tri" id={`triangle-${visualId}`} bind:this={triangleElement} />
</div>

<style>
   .tri {
      width: 0;
      height: 0;
      margin: 1.5rem;
      margin-left: 1rem;

      border-bottom-style: solid;
      border-left-style: solid;
      border-left-color: transparent;
      border-right-style: solid;
      border-right-color: transparent;
   }
</style>
