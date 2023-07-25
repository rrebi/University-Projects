from rest_framework import serializers
from .models import Books, Publisher, Customers, BookSold

# converting objects into data types understandable by javascript and front-end frameworks (json)
# visible also to clients


class BookSerializer(serializers.ModelSerializer):
    name = serializers.CharField(max_length=255)
    description = serializers.CharField(max_length=255)
    author = serializers.CharField(max_length=255)
    review = serializers.CharField(max_length=255)
    stars = serializers.IntegerField(default=0)
    publisher = serializers.SlugRelatedField(queryset=Publisher.objects.all(), slug_field='publisher')

    class Meta:
        model = Books
        fields = ['id', 'name', 'description', 'author', 'review', 'stars', 'publisher']
        # depth = 1


class BookDetailSerializer(serializers.ModelSerializer):
    customers = serializers.SerializerMethodField(read_only=True)  # for customers buy books

    class Meta:
        model = Books
        fields = ['id', 'name', 'description', 'author', 'review', 'stars', 'publisher', 'customers']
        depth = 1

    # for customers buy books
    def get_customers(self, obj):
        customers = BookSold.objects.filter(books_id=obj)
        return BooksSoldSerializer(customers, many=True).data


class PublisherSerializer(serializers.ModelSerializer):
    class Meta:
        model = Publisher
        fields = ['id', 'publisher', 'year', 'owner_name', 'format', 'country']


class PublisherDetailSerializer(serializers.ModelSerializer):
    books = BookSerializer(many=True, read_only=True)

    class Meta:
        model = Publisher
        fields = ['id', 'publisher', 'year', 'owner_name', 'format', 'country', 'books']


class CustomerSerializer(serializers.ModelSerializer):
    class Meta:
        model = Customers
        fields = ['id', 'name_of_customer', 'year_of_birth', 'address', 'gender', 'phone']


class CustomerDetailSerializer(serializers.ModelSerializer):
    customers_books = serializers.SerializerMethodField()  # for customers buy books

    class Meta:
        model = Customers
        fields = ['id', 'name_of_customer', 'year_of_birth', 'address', 'gender', 'phone', 'customers_books']

    def get_customers_books(self, obj):
        customers_books = BookSold.objects.filter(customers_id=obj)
        return BooksSoldSerializer(customers_books, many=True).data


class CustomerFilterSerializer(serializers.ModelSerializer):
    year_of_birth = serializers.IntegerField(read_only=True)

    class Meta:
        model = Customers
        fields = ['id', 'year_of_birth']


class BooksSoldSerializer(serializers.ModelSerializer):
    customers_id = serializers.SlugRelatedField(queryset=Customers.objects.all(), slug_field='id')
    books_id = serializers.SlugRelatedField(queryset=Books.objects.all(), slug_field='id')

    class Meta:
        model = BookSold
        fields = ['id', 'amount', 'date', 'customers_id', 'books_id']


class BooksSoldDetailSerializer(serializers.ModelSerializer):
    class Meta:
        model = BookSold
        fields = ['id', 'amount', 'date', 'customers_id', 'books_id']
        depth = 1


class StatisticsSerializer(serializers.ModelSerializer):
    avg_stars = serializers.IntegerField(read_only=True)
    book_count = serializers.IntegerField(read_only=True)

    class Meta:
        model = Publisher
        fields = ['id', 'publisher', 'avg_stars', 'book_count']


class StatisticsSerializer2(serializers.ModelSerializer):
    avg_amount = serializers.IntegerField(read_only=True)
    books_sold_count = serializers.IntegerField(read_only=True)

    class Meta:
        model = Customers
        fields = ['id', 'name_of_customer', 'avg_amount', 'books_sold_count']
