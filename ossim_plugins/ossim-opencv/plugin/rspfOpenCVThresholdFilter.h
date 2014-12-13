#ifndef rspfOpenCVThresholdFilter_HEADER
#define rspfOpenCVThresholdFilter_HEADER

#include "rspf/plugin/rspfSharedObjectBridge.h"
#include "rspf/base/rspfString.h"
#include "rspf/imaging/rspfImageSourceFilter.h"

#include "cv.h"

/** 

@brief OpenCV Threshold Filter 

Applies a fixed-level threshold to array elements.

@param src Source array (single-channel, 8-bit or 32-bit floating point)
@param dst Destination array; must be either the same type as src or 8-bit
@param threshold Threshold value
@param maxValue Maximum value to use with CV_THRESH_BINARY and CV_THRESH_BINARY_INV thresholding types
@param thresholdType – Thresholding type (see the discussion)

The function applies fixed-level thresholding to a single-channel array. The function is typically used to get a bi-level (binary) image out of a grayscale image or for removing a noise, i.e. filtering out pixels with too small or too large values. There are several types of thresholding that the function supports that are determined by thresholdType:

<ul> <li> <b> CV_THRESH_BINARY </b> - </li> </ul> 
\image html CV_THRESH_BINARY.png
<ul> <li> <b> CV_THRESH_BINARY_INV </b> - </li> </ul> 
\image html CV_THRESH_BINARY_INV.png
<ul> <li> <b> CV_THRESH_TRUNC </b> - </li> </ul> 
\image html CV_THRESH_TRUNC.png
<ul> <li> <b> CV_THRESH_TOZERO </b> - </li> </ul> 
\image html CV_THRESH_TOZERO.png
<ul> <li> <b> CV_THRESH_TOZERO_INV </b>- </li> </ul> 
\image html CV_THRESH_TOZERO_INV.png

Also, the special value <b>CV_THRESH_OTSU</b> may be combined with one of the above values. In this case the function determines the optimal threshold value using Otsu’s algorithm and uses it instead of the specified thresh. The function returns the computed threshold value. Currently, Otsu’s method is implemented only for 8-bit images.

\image html threshold.png

**/


class rspfOpenCVThresholdFilter : public rspfImageSourceFilter
{

public:
/*
   enum rspfOpenCVThresholdFilterType
   {
		CV_THRESH_BINARY=0,
		CV_THRESH_BINARY_INV=1,
		CV_THRESH_TRUNC=2,
		CV_THRESH_TOZERO=3,
		CV_THRESH_TOZERO_INV=4,
		CV_THRESH_MASK=5,
		CV_THRESH_OTSU=6
   };
*/
   rspfOpenCVThresholdFilter(rspfObject* owner=NULL);

   virtual ~rspfOpenCVThresholdFilter();

   rspfString getShortName()const
      {
         return rspfString("OpenCVThreshold");
      }
   rspfString getLongName()const
      {
         return rspfString("OpenCV Threshold Filter");
      }
   
   virtual rspfRefPtr<rspfImageData> getTile(const rspfIrect& tileRect, rspf_uint32 resLevel=0);
   
   virtual void initialize();
   
   virtual rspfScalarType getOutputScalarType() const;
   
   rspf_uint32 getNumberOfOutputBands() const;
 
   virtual bool saveState(rspfKeywordlist& kwl,
                          const char* prefix=0)const;
   
   /*!
    * Method to the load (recreate) the state of an object from a keyword
    * list.  Return true if ok or false on error.
    */
   virtual bool loadState(const rspfKeywordlist& kwl,
                          const char* prefix=0);

   /*
   * Methods to expose thresholds for adjustment through the GUI
   */
   virtual void setProperty(rspfRefPtr<rspfProperty> property);
   virtual rspfRefPtr<rspfProperty> getProperty(const rspfString& name)const;
   virtual void getPropertyNames(std::vector<rspfString>& propertyNames)const;


protected:
   rspfRefPtr<rspfImageData> theTile;///< Output tile
   double theThreshold;///< Threshold value
   double theMaxValue;///< Maximum value to use with CV_THRESH_BINARY and CV_THRESH_BINARY_INV  thresholding types
   int theThresholdType;///< Thresholding type (see the detailed description)
   void runUcharTransformation(rspfImageData* tile);

private:
	void setThresholdtype(const rspfString& lookup);///< Lookup Threshold Type
	void getThresholdTypeList(std::vector<rspfString>& list) const;
	rspfString getThresholdTypeString() const;



TYPE_DATA
};

#endif
