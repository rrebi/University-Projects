from rest_framework import serializers
from .models import Books
from .models import Publisher
from .models import Customers
from django.db import models

# converting objects into data types understandable by javascript and front-end frameworks (json)
# visible also to clients


class BookSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    description = serializers.CharField(max_length=255)
    author = serializers.CharField(max_length=255)#(read_only=True)
    review = serializers.CharField(max_length=255)#(read_only=True)
    stars = serializers.IntegerField(default=0)#(read_only=True)
    publisher = serializers.SlugRelatedField(queryset=Publisher.objects.all(), slug_field='publisher')

    class Meta:
        model = Books
        fields = ['id', 'name', 'description', 'author', 'review', 'stars', 'publisher']
        # depth = 1


class BookDetailSerializer(serializers.ModelSerializer):
    class Meta:
        model = Books
        fields = ['id', 'name', 'description', 'author', 'review', 'stars', 'publisher']
        depth = 1


class PublisherSerializer(serializers.ModelSerializer):
    class Meta:
        model = Publisher
        fields = ['id', 'publisher', 'year', 'owner_name', 'format', 'city']


class PublisherDetailSerializer(serializers.ModelSerializer):
    books = BookSerializer(many=True, read_only=True)
    class Meta:
        model = Publisher
        fields = ['id', 'publisher', 'year', 'owner_name', 'format', 'city', 'books']
        #fields = ['id','book']


class CustomerSerializer(serializers.ModelSerializer):
    class Meta:
        model = Customers
        fields = ['id', 'name', 'year_of_birth', 'address', 'gender', 'phone']


class CustomerFilterSerializer(serializers.ModelSerializer):
    year_of_birth = serializers.IntegerField(read_only=True)
    class Meta:
        model = Customers
        fields = ['id', 'year_of_birth']

