import { Component, OnInit } from '@angular/core';
import { News } from 'src/app/news';
import { NewsService } from 'src/app/newsservice';
import { Location } from '@angular/common';
import { Router } from '@angular/router';
import { ROLE } from '../login/login.component';


@Component({
  selector: 'app-update',
  templateUrl: './update.component.html',
  styleUrls: ['./update.component.css']
})
export class UpdateComponent implements OnInit {

  news: News[] = [];
  selectedNews: News = { Title: '', Text: '', Producer: '', Date: new Date(), Category: '' };

  constructor(private newsService: NewsService, private location: Location, private router: Router) {}

  ngOnInit() {
    if (ROLE.role !== 'user') {
      this.router.navigate(['/login']);
    } else {
      this.getNews();
    }
  }

  getNews() {
    this.newsService.getAllNews().subscribe(
      (data: any) => {
        this.news = data;
        console.log(this.news);
      }
    );
  }

  selectNews(news: News) {
    this.selectedNews = { ...news };
  }

  updateEntry() {
    if (ROLE.role === 'user') {
      this.newsService.updateNews(this.selectedNews).subscribe(
        (response) => {
          console.log('Update successful:', response);
          this.getNews();
        }
      );
    } else {
      console.log('Failed! No rights.');
    }
  }

  confirmUpdate() {
    if (confirm('Are you sure you want to update this entry?')) {
      this.updateEntry();
    } else {
      // Handle cancellation, e.g., show a message or perform fallback action
    }
  }
}
