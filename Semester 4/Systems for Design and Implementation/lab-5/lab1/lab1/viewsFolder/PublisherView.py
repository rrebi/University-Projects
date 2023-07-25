from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import Publisher
from lab1.serializers import PublisherSerializer, PublisherDetailSerializer


class PublisherAPIView(APIView):
    @api_view(['GET', 'POST'])
    def publisher_list(request, format=None):
        if request.method == 'GET':
            publisher = Publisher.objects.all()
            serializer = PublisherSerializer(publisher, many=True)

            return Response(serializer.data)

        if request.method == 'POST':
            serializer = PublisherSerializer(data=request.data)

            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            print(serializer.errors)
            return Response(status=status.HTTP_404_NOT_FOUND)

    @api_view(['GET', 'PUT', 'DELETE'])
    def publisher_detail(request, id, format=None):

        try:
            publisher = Publisher.objects.get(pk=id)
        except Publisher.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            serializer = PublisherDetailSerializer(publisher)
            return Response(serializer.data)

        elif request.method == 'PUT':
            # update
            serializer = PublisherSerializer(publisher, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        elif request.method == 'DELETE':
            publisher.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)

