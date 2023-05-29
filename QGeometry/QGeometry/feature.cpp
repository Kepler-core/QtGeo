#include"feature.h"
#include"layer.h"

//GeoFeatureLayer->layer.h
//×Ö¶ÎÒªËØ
GeoFeature::GeoFeature(GeoFeatureLayer* layerParent) :fieldDefns(layerParent->getFieldDefns())
{
    initNewFieldValue();
}

GeoFeature::GeoFeature(std::vector<GeoFieldDefn*>* fieldDefnsIn) :fieldDefns(fieldDefnsIn)
{
    initNewFieldValue();
}

GeoFeature::GeoFeature(int nFID, GeoFeatureLayer* layerParent) :nFID(nFID), fieldDefns(layerParent->getFieldDefns())
{
    initNewFieldValue();
}

GeoFeature::GeoFeature(int nFID, std::vector<GeoFieldDefn*>* fieldDefnsIn) :nFID(nFID), fieldDefns(fieldDefnsIn)
{
    initNewFieldValue();
}