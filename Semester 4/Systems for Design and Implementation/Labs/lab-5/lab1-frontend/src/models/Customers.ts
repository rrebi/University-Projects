import { BookSold } from "./BookSold";

export interface Customers{
    id:number;
    name_of_customer:string;
    year_of_birth:number;
    address:string;
    gender:string;
    phone:number;
    books_sold:BookSold[];
}