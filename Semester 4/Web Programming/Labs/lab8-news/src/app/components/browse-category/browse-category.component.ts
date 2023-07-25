import { Component, OnInit } from '@angular/core';
import { News } from 'src/app/news';
import { NewsService } from 'src/app/newsservice';

@Component({
  selector: 'app-browse',
  templateUrl: './browse-category.component.html',
  styleUrls: ['./browse-category.component.css']
})
export class BrowseCategoryComponent implements OnInit {
  filterByCategory: string = '';
  news: News[] = [];
  previousFilters: string[] = [];

  constructor(private newsService: NewsService) {}

  ngOnInit(): void {}

  searchNews(): void {
    if (this.filterByCategory) {
      this.newsService.getNews(this.filterByCategory).subscribe((data) => {
        this.news = Array.isArray(data) ? data : [data]; // Ensure data is an array
      });
    } else {
      this.newsService.getAllNews().subscribe((data) => {
        this.news = Array.isArray(data) ? data : [data]; // Ensure data is an array
      });
    }
  
    // Add current filter to the previousFilters array
    this.previousFilters.push(this.filterByCategory);
  }
  
}
