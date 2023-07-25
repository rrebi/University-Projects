import { ComponentFixture, TestBed } from '@angular/core/testing';

import { BrowseDateComponent } from './browse-date.component';

describe('BrowseDateComponent', () => {
  let component: BrowseDateComponent;
  let fixture: ComponentFixture<BrowseDateComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [BrowseDateComponent]
    });
    fixture = TestBed.createComponent(BrowseDateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
