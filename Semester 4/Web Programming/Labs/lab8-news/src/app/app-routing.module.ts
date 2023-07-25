import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AddComponent } from './components/add/add.component';
import { BrowseCategoryComponent } from './components/browse-category/browse-category.component';
import { BrowseDateComponent } from './components/browse-date/browse-date.component';
import { UpdateComponent } from './components/update/update.component';
import { LoginComponent } from './components/login/login.component';

const routes: Routes = [
  {path: 'addnews', component: AddComponent},
  {path: 'browsenews', component: BrowseCategoryComponent},
  {path: 'browsenewsdate', component: BrowseDateComponent},
  {path: 'updatenews', component: UpdateComponent},
  {path: 'login', component: LoginComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
