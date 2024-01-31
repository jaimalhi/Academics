// white-pig.ts
import { Pig } from "../pig";

export class WhitePig implements Pig {
   category: string = "White";
   name: string;
   breed: string;
   height: number;
   weight: number;
   personality: string;
   attributes: { runningAbility: number };
   constructor(
      name: string,
      breed: string,
      height: number,
      weight: number,
      personality: string,
      runningAbility: number
   ) {
      this.name = name;
      this.breed = breed;
      this.height = height;
      this.weight = weight;
      this.personality = personality;
      this.attributes = { runningAbility };
   }
}
