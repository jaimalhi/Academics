//grey-pig.ts
import { Pig } from "../pig";

export class GreyPig implements Pig {
   category: string = "Grey";
   name: string;
   breed: string;
   height: number;
   weight: number;
   personality: string;
   attributes: { swimmingAbility: number };
   constructor(
      name: string,
      breed: string,
      height: number,
      weight: number,
      personality: string,
      swimmingAbility: number
   ) {
      this.name = name;
      this.breed = breed;
      this.height = height;
      this.weight = weight;
      this.personality = personality;
      this.attributes = { swimmingAbility };
   }
}
