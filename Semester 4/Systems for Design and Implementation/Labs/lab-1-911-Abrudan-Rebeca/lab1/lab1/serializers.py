from rest_framework import serializers
from .models import Books

# converting objects into data types understandable by javascript and front-end frameworks (json)
# visible also to clients

class BookSerializer(serializers.ModelSerializer):
    class Meta:
        model = Books
        fields = ['id', 'name', 'description', 'author', 'review', 'stars']
