import { Publisher } from "./Publisher";
import { BookSold } from "./BookSold";


export interface Books
{
    id:number;
    name:string;description:string;
    author:string;
    review:string;
    stars:number;
    publisher:Publisher;
    customers:BookSold[];
}