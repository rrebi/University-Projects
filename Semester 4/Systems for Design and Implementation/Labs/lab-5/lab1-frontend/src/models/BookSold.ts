import { Books } from "./Books";
import { Customers } from "./Customers";

export interface BookSold{
    id:number;
    amount:number;
    date:Date;
    customers_id:Customers;
    books_id:Books;
}