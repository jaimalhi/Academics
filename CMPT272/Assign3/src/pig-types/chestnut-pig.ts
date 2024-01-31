// chestnut-pig.ts
import { Pig } from "../pig";

export class ChestnutPig implements Pig {
   category: string = "Chestnut";
   name: string;
   breed: string;
   height: number;
   weight: number;
   personality: string;
   attributes: { language: string };
   constructor(
      name: string,
      breed: string,
      height: number,
      weight: number,
      personality: string,
      language: string
   ) {
      this.name = name;
      this.breed = breed;
      this.height = height;
      this.weight = weight;
      this.personality = personality;
      this.attributes = { language };
   }
}
