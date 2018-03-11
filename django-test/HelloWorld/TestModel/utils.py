# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from rest_framework.serializers import ValidationError


class Validation(object):

    @staticmethod
    def check_missing_property(type, required_props, data):
        for k, v in data.items():
            if v in ['None', '']:
                data[k] = None
        error_props = []
        for prop in required_props:
            if (prop not in data) or (not data[prop]):
                error_props.append(prop)

        if error_props:
            raise ValidationError(
                detail='The %(type)s\'s property %(prop)s should not be '
                       'empty. The %(type)s: %(data)s/' % {
                           'type': type,
                           'prop': error_props,
                           'data': data,
                       },
                code='InvalidProperty'
            )

        return data


		

