import { Component, OnInit } from '@angular/core';
import { News } from 'src/app/news';
import { NewsService } from 'src/app/newsservice';

@Component({
  selector: 'app-browse',
  templateUrl: './browse-date.component.html',
  styleUrls: ['./browse-date.component.css']
})
export class BrowseDateComponent implements OnInit {
  filterByDate: string = '';
  news: News[] = [];
  previousFilters: string[] = [];

  constructor(private newsService: NewsService) {}

  ngOnInit(): void {}

  searchNews(): void {
    if (this.filterByDate) {
      this.newsService.getNewsDate(this.filterByDate).subscribe((data) => {
        this.news = Array.isArray(data) ? data : [data]; // Ensure data is an array
        console.log(this.news);
      });
    } else {
      this.newsService.getAllNews().subscribe((data) => {
        this.news = Array.isArray(data) ? data : [data]; // Ensure data is an array
        console.log(this.news);
      });
    }
  
    // Add current filter to the previousFilters array
    this.previousFilters.push(this.filterByDate);
  }
}
