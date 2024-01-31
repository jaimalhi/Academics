// add-pig.ts
import { Pig } from "./pig";
import { BlackPig } from "./pig-types/black-pig";
import { ChestnutPig } from "./pig-types/chestnut-pig";
import { GreyPig } from "./pig-types/grey-pig";
import { WhitePig } from "./pig-types/white-pig";

let addModalVisible = false;
const addPigModal = document.querySelector(".add-modal");
const addBtn = document.getElementById("add-pig") as HTMLButtonElement;
const overlay = document.getElementById("overlay") as HTMLDivElement;

function openCloseModalHelper(): void {
   if (addModalVisible) {
      // modal visible -> hidden
      addPigModal?.classList.add("hidden");
      overlay.classList.add("hidden");
      addBtn.innerText = "Add Pig";
   } else {
      // modal hidden -> visible
      addPigModal?.classList.remove("hidden");
      overlay.classList.remove("hidden");
      addBtn.innerText = "Close Modal";
   }
   addModalVisible = !addModalVisible;
}

function clearInputsValues(
   nameInput: HTMLInputElement,
   breedInput: HTMLInputElement,
   heightInput: HTMLInputElement,
   weightInput: HTMLInputElement,
   personalitySelect: HTMLSelectElement,
   categorySelect: HTMLSelectElement,
   blackPigInput: HTMLInputElement,
   chestnutPigInput: HTMLInputElement,
   greyPigInput: HTMLInputElement,
   whitePigInput: HTMLInputElement
): void {
   //reset values
   nameInput.value = "";
   breedInput.value = "";
   heightInput.value = "";
   weightInput.value = "";
   personalitySelect.value = "Personality";
   categorySelect.value = "Category";
   blackPigInput.value = "";
   chestnutPigInput.value = "";
   greyPigInput.value = "";
   whitePigInput.value = "";
}

function showErrorModal(): void {
   const errorModal = document.getElementById("error-modal") as HTMLDivElement;
   const closeError = document.getElementById("close-error-modal") as HTMLButtonElement;
   errorModal.classList.remove("hidden");

   closeError.addEventListener("click", () => {
      errorModal.classList.add("hidden");
   });

   // hide modal after 2s
   setTimeout(() => {
      errorModal.classList.add("hidden");
   }, 2000);
}

export function openCloseModal(): void {
   const addBtn = document.getElementById("add-pig") as HTMLButtonElement;
   addBtn.addEventListener("click", () => {
      openCloseModalHelper();
   });
   const closeAddModal = document.getElementById("close-add-modal") as HTMLButtonElement;
   closeAddModal.addEventListener("click", () => {
      openCloseModalHelper();
   });
}

export function addNewPig(): void {
   const addNewPig = document.getElementById("submit-new-pig") as HTMLButtonElement;
   const nameInput = document.getElementById("name-select") as HTMLInputElement;
   const breedInput = document.getElementById("breed-select") as HTMLInputElement;
   const heightInput = document.getElementById("height-select") as HTMLInputElement;
   const weightInput = document.getElementById("weight-select") as HTMLInputElement;
   const personalitySelect = document.getElementById("personality-select") as HTMLSelectElement;
   const categorySelect = document.getElementById("category-select") as HTMLSelectElement;

   const inputs: (HTMLInputElement | HTMLSelectElement)[] = [
      nameInput,
      breedInput,
      heightInput,
      weightInput,
      personalitySelect,
      categorySelect,
   ];
   // Function to check if all fields are filled
   function checkFields(): void {
      for (const input of inputs) {
         if (!input.value) {
            addNewPig.disabled = true;
            return;
         }
      }
      addNewPig.disabled = false;
   }

   // Event listeners for input fields
   inputs.forEach((input) => {
      input.addEventListener("input", checkFields);
   });

   //add new pig to local storage
   addNewPig.addEventListener("click", () => {
      const newName = nameInput.value;
      const newBreed = breedInput.value;
      const newHeight = heightInput.value;
      const newWeight = weightInput.value;
      const newPersonality = personalitySelect.value;
      const newCategory = categorySelect.value;

      //check height & weight inputs
      if (
         parseInt(newHeight) < 0 ||
         parseInt(newHeight) > 500 ||
         parseInt(newWeight) < 0 ||
         parseInt(newWeight) > 2500
      ) {
         showErrorModal();
         return;
      }

      // get additional field info
      const blackPigInput = document.querySelector(".black-pig-fields input") as HTMLInputElement;
      const chestnutPigInput = document.querySelector(
         ".chestnut-pig-fields input"
      ) as HTMLInputElement;
      const greyPigInput = document.querySelector(".grey-pig-fields input") as HTMLInputElement;
      const whitePigInput = document.querySelector(".white-pig-fields input") as HTMLInputElement;
      let additionalField: string | number = "";
      switch (newCategory) {
         case "black-pig":
            additionalField = parseInt(blackPigInput.value);
            if (additionalField < 0 || additionalField > 10) {
               showErrorModal();
               return;
            }
            break;
         case "chestnut-pig":
            additionalField = chestnutPigInput.value;
            break;
         case "grey-pig":
            additionalField = parseInt(greyPigInput.value);
            if (additionalField < 0 || additionalField > 100) {
               showErrorModal();
               return;
            }
            break;
         case "white-pig":
            additionalField = parseInt(whitePigInput.value);
            if (additionalField < 0 || additionalField > 100) {
               showErrorModal();
               return;
            }
            break;
         default:
            break;
      }

      let newPig: Pig | null = null;

      switch (newCategory) {
         case "black-pig":
            newPig = new BlackPig(
               newName,
               newBreed,
               +newHeight,
               +newWeight,
               newPersonality,
               +additionalField
            );
            break;
         case "chestnut-pig":
            newPig = new ChestnutPig(
               newName,
               newBreed,
               +newHeight,
               +newWeight,
               newPersonality,
               additionalField.toString()
            );
            break;
         case "grey-pig":
            newPig = new GreyPig(
               newName,
               newBreed,
               +newHeight,
               +newWeight,
               newPersonality,
               +additionalField
            );
            break;
         case "white-pig":
            newPig = new WhitePig(
               newName,
               newBreed,
               +newHeight,
               +newWeight,
               newPersonality,
               +additionalField
            );
            break;
         default:
            console.log("=== Error ===\nPig Category Invalid");
            break;
      }

      if (newPig) {
         const existingPigsJSON = localStorage.getItem("pigs");
         const existingPigs = existingPigsJSON ? JSON.parse(existingPigsJSON) : [];

         existingPigs.push(newPig);
         localStorage.setItem("pigs", JSON.stringify(existingPigs));
      }

      openCloseModalHelper();
      clearInputsValues(
         nameInput,
         breedInput,
         heightInput,
         weightInput,
         personalitySelect,
         categorySelect,
         blackPigInput,
         chestnutPigInput,
         greyPigInput,
         whitePigInput
      );
      location.reload(); // force refresh page
   });
}

export function additionalFieldsForCategories(): void {
   // Additional options for adding pig category, hides elements on load
   const categorySelect = document.getElementById("category-select") as HTMLSelectElement;
   const additionalFields = document.querySelector(".additional-fields");
   categorySelect.addEventListener("change", () => {
      const selectedCategory = categorySelect.value;

      if (additionalFields) {
         const allFieldGroups = additionalFields.querySelectorAll(".form-group");

         if (allFieldGroups) {
            allFieldGroups.forEach((fieldGroup: Element) => {
               if (fieldGroup instanceof HTMLElement) {
                  fieldGroup.style.display = "none";
               }
            });

            if (selectedCategory) {
               const selectedFieldGroup = additionalFields.querySelector(
                  `.${selectedCategory}-fields`
               );
               if (selectedFieldGroup instanceof HTMLElement) {
                  additionalFields?.classList.remove("hidden");
                  selectedFieldGroup.style.display = "block";
               }
            }
         }
      }
   });
}
