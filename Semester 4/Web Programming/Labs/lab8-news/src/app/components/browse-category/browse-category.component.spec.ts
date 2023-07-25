import { ComponentFixture, TestBed } from '@angular/core/testing';

import { BrowseCategoryComponent } from './browse-category.component';

describe('BrowseCategoryComponent', () => {
  let component: BrowseCategoryComponent;
  let fixture: ComponentFixture<BrowseCategoryComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [BrowseCategoryComponent]
    });
    fixture = TestBed.createComponent(BrowseCategoryComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
