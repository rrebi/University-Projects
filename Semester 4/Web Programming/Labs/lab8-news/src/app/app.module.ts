import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LoginComponent } from './components/login/login.component';
import { AddComponent } from './components/add/add.component';
import { BrowseCategoryComponent } from './components/browse-category/browse-category.component';
import { BrowseDateComponent } from './components/browse-date/browse-date.component';
import { UpdateComponent } from './components/update/update.component';
import { FormsModule } from '@angular/forms';
import { NavigationComponent } from './navigation/navigation.component';

@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    AddComponent,
    BrowseCategoryComponent,
    BrowseDateComponent,
    UpdateComponent,
    LoginComponent,
    NavigationComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule

  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
