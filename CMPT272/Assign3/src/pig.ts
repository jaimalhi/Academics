// pig.ts
export interface Pig {
   readonly category: string;
   name: string;
   breed: string;
   height: number;
   weight: number;
   personality: string;
   attributes: Record<string, number | string>; //attributes based on the category
}
