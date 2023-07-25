from django.db import models

# the data you want to present, usually data from a database.
# visible to developer only
# data is created in objects, called Models, and is actually tables in a database.


class Books(models.Model):
    name = models.CharField(max_length=200, default='')

    description = models.CharField(max_length=500, default='')

    author=models.CharField(max_length=500, default='')
    review = models.CharField(max_length=500, default='')
    stars = models.IntegerField(default="0")

    def __str__(self):
        return self.name + ' ' + self.description  + ' ' + self.author + ' ' + self.review + ' ' + str(self.stars)
