import { Component } from '@angular/core';
import { NewsService } from 'src/app/newsservice';
import { Router } from '@angular/router';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  username: string = '';
  password: string = '';

  constructor(private router: Router, private newsService: NewsService) {}

  login() {
    this.newsService.login(this.username, this.password).subscribe(
      (response: any) => {
        // Check the response for successful login
        if (response) {
          // Redirect to addnews.html or perform any other actions upon successful login
          if (response === 'user') {
            ROLE.role = 'user';
          } else {
            ROLE.role = '';
          }

          this.router.navigate(['/addnews']);
        } else {
          alert('Invalid credentials');
        }
      }
    );

    // Reset the form fields after login
    this.username = '';
    this.password = '';
  }

  skipLogin() {
    ROLE.role = 'visitator';

    // Redirect to addnews.html or any other desired page
    this.router.navigate(['/browsenews']);
  }
}

export const ROLE = {
  role: ''
};
