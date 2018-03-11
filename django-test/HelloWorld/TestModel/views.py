# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from rest_framework import viewsets
from TestModel import models
from TestModel import serializers

# Create your views here.
class ProjectViewSet(viewsets.ModelViewSet):
    queryset = models.Project.objects.all()
    serializer_class = serializers.ProjectSerializer
