import { Component, OnInit } from '@angular/core';
import { News } from 'src/app/news';
import { NewsService } from 'src/app/newsservice';
import { Router } from '@angular/router';
import { ROLE } from '../login/login.component';

@Component({
  selector: 'app-add',
  templateUrl: './add.component.html',
  styleUrls: ['./add.component.css']
})
export class AddComponent implements OnInit {
  news: News = {} as News;
  errorMessage: string = '';

  constructor(private newsService: NewsService, private router: Router) { }

  ngOnInit(): void {
    if (ROLE.role !== 'user') {
      this.router.navigate(['/login']); // Redirect to login page
    }
  }

  handleAdd(): void {
    if (ROLE.role == "user") {
      if (!this.news.Title || !this.news.Text || !this.news.Producer || !this.news.Date || !this.news.Category) {
        this.errorMessage = 'Please fill in all fields.';
        return;
      }
  
      this.newsService.addNews(this.news).subscribe(
        (response) => {
          window.alert('News added successfully!');
          this.news = {} as News;
          this.errorMessage = '';
        },
        (error) => {
          window.alert('Failed to add news. Please try again.');
          console.error(error);
        }
      );
    } else {
      this.router.navigate(['/login']); // Redirect to login page
    }
  }
  
  
}
