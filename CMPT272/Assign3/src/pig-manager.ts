// pig-manager.ts
import { Pig } from "./pig";
import { openCloseModal, addNewPig, additionalFieldsForCategories } from "./add-pig";

export class PigManager {
   private pigs: Pig[] = [];

   constructor() {
      const storedPigs = localStorage.getItem("pigs");
      if (storedPigs) {
         this.pigs = JSON.parse(storedPigs);
      }
   }

   addPig(): void {
      openCloseModal();
      addNewPig();
      additionalFieldsForCategories();
   }

   displayPigs(): void {
      this.sortByCategory();
      console.log(this.pigs);
      const tableBody = document.querySelector("tbody");
      if (tableBody) {
         tableBody.innerHTML = ""; // Clear the table body before re-rendering

         this.pigs.forEach((pig: any) => {
            const row = document.createElement("tr");
            const nameCell = document.createElement("td");
            nameCell.textContent = pig.name;
            row.appendChild(nameCell);

            const categoryCell = document.createElement("td");
            categoryCell.textContent = pig.category;
            row.appendChild(categoryCell);

            const moreInfoCell = document.createElement("td");
            const moreInfoButton = document.createElement("button");
            moreInfoButton.classList.add("btn", "btn-info");
            moreInfoButton.textContent = "More Info";
            moreInfoButton.addEventListener("click", () => {
               this.showMoreInfo(pig); // Function to show more info for this pig
            });
            moreInfoCell.appendChild(moreInfoButton);
            row.appendChild(moreInfoCell);

            const deleteCell = document.createElement("td");
            const deleteButton = document.createElement("button");
            deleteButton.classList.add("btn", "btn-danger");
            deleteButton.textContent = "Delete";
            deleteButton.addEventListener("click", () => {
               this.deletePig(pig); // Function to delete this pig
               this.displayPigs();
               // tableBody.removeChild(row); // Remove the row after deletion
            });
            deleteCell.appendChild(deleteButton);
            row.appendChild(deleteCell);

            tableBody.appendChild(row);
         });
      }
   }

   showMoreInfo(pig: Pig): void {
      console.log(pig);
      const overlay = document.getElementById("overlay") as HTMLDivElement;
      const infoModal = document.getElementById("info-modal") as HTMLDivElement;
      const closeInfo = document.getElementById("close-info-btn") as HTMLButtonElement;

      // grab li to fill with info
      const pName = document.getElementById("p-name") as HTMLHeadingElement;
      const pBreed = document.getElementById("p-breed") as HTMLSpanElement;
      const pCategory = document.getElementById("p-category") as HTMLSpanElement;
      const pHeight = document.getElementById("p-height") as HTMLSpanElement;
      const pWeight = document.getElementById("p-weight") as HTMLSpanElement;
      const pPersonality = document.getElementById("p-personality") as HTMLSpanElement;
      const pAttributeName = document.getElementById("p-attr-name") as HTMLSpanElement;
      const pAttributeValue = document.getElementById("p-attr-value") as HTMLSpanElement;

      // show info modal
      infoModal.classList.remove("hidden");
      overlay.classList.remove("hidden");

      closeInfo.addEventListener("click", () => {
         infoModal.classList.add("hidden");
         overlay.classList.add("hidden");
      });

      // update with pig info
      pName.innerText = pig.name;
      pBreed.innerText = pig.breed;
      pCategory.innerText = pig.category;
      pHeight.innerText = pig.height.toString();
      pWeight.innerText = pig.weight.toString();
      pPersonality.innerText = pig.personality;

      // Access keys and values of the 'attributes' record
      const [attrKey, attrValue] = this.showPigAttribute(pig);
      pAttributeName.innerText = attrKey;
      pAttributeValue.innerText = attrValue;
   }

   deletePig(pig: Pig): void {
      console.log(pig);
      const deletePigModal = document.getElementById("confirm-delete-modal") as HTMLDivElement;
      const closeDelete = document.getElementById("close-delete-modal") as HTMLButtonElement;
      const confirmDelete = document.getElementById("confirm-delete-btn") as HTMLButtonElement;
      const overlay = document.getElementById("overlay") as HTMLDivElement;

      deletePigModal.classList.remove("hidden");
      overlay.classList.remove("hidden");
      closeDelete.addEventListener("click", () => {
         deletePigModal.classList.add("hidden");
         overlay.classList.add("hidden");
      });
      confirmDelete.addEventListener("click", () => {
         // delete the pig
         this.confirmPigDeletion(pig);
         this.displayPigs();
         deletePigModal.classList.add("hidden");
         overlay.classList.add("hidden");
      });
   }

   private savePigs(): void {
      localStorage.setItem("pigs", JSON.stringify(this.pigs));
   }

   private sortByCategory(): void {
      // Sorting the array by the 'category' field
      this.pigs.sort((a, b) => {
         if (a.category < b.category) {
            return -1;
         }
         if (a.category > b.category) {
            return 1;
         }
         return 0;
      });
   }

   private confirmPigDeletion(pig: Pig): void {
      const index = this.pigs.findIndex((p) => p === pig);
      if (index !== -1) {
         this.pigs.splice(index, 1);
         this.savePigs();
      }
   }

   private showPigAttribute(pig: Pig): [string, string] {
      let attrKey: string = "";
      let attrValue: string | number = -1;
      for (const [key, value] of Object.entries(pig.attributes)) {
         attrKey = key;
         attrValue = value;
      }

      switch (attrKey) {
         case "strength":
            attrKey = "Strength";
            break;
         case "language":
            attrKey = "Language";
            break;
         case "swimmingAbility":
            attrKey = "Swimming Ability";
            break;
         case "runningAbility":
            attrKey = "Running Ability";
            break;
         default:
            break;
      }
      return [attrKey, attrValue.toString()];
   }
}
