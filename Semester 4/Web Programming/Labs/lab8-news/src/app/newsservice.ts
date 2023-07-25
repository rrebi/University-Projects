import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs';
import { News } from './news';// Replace 'path/to/news.interface' with the actual path to your News interface

@Injectable({
  providedIn: 'root'
})
export class NewsService {
  private API: string = 'http://localhost/news/PHP'; // Replace with your API URL

  constructor(private http: HttpClient) { }


  getNews(filterByCategory: string): Observable<News[]> {
    const params = new HttpParams()
      //.set('filter_by_date', filterByDate)
      .set('filter_by_category', filterByCategory)

    const url = `${this.API}/ViewByCategory.php`;
    return this.http.get<News[]>(url, { params });
  }

  getNewsDate(filterByDate: string): Observable<News[]> {
    const params = new HttpParams()
      .set('filter_by_date', filterByDate)
      //.set('filter_by_category', filterByCategory)

    const url = `${this.API}/ViewByDate.php`;
    return this.http.get<News[]>(url, { params });
  }

  
  getAllNews(): Observable<News[]>{
    const url = `${this.API}/ViewAll.php`;
    return this.http.get<News[]>(url);
  }

  addNews(news: News): Observable<any> {
    
    return this.http.post(`${this.API}/AddNews.php`, news);
  }

  
  updateNews(news: News): Observable<any> {
    return this.http.put(`${this.API}/UpdateNews.php`, news);
  }

  login(username: string, password: string): Observable<any> {
    const formData = new FormData();
    formData.append('username', username);
    formData.append('password', password);
    
    return this.http.post(`${this.API}/login.php`, formData);
  }


}
