// black-pig.ts
import { Pig } from "../pig";

export class BlackPig implements Pig {
   category: string = "Black";
   name: string;
   breed: string;
   height: number;
   weight: number;
   personality: string;
   attributes: { strength: number };
   constructor(
      name: string,
      breed: string,
      height: number,
      weight: number,
      personality: string,
      strength: number
   ) {
      this.name = name;
      this.breed = breed;
      this.height = height;
      this.weight = weight;
      this.personality = personality;
      this.attributes = { strength };
   }
}
