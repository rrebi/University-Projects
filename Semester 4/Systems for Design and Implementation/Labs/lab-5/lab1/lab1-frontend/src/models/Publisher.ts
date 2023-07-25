import { Books } from "./Books";


export interface Publisher{
    id?:number;
    publisher:string;
    year:number;
    owner_name:string;
    format:string;
    country:string;
    books?:Books[];
}