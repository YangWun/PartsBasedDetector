/* 
 *  Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  File:    IFeatures.hpp
 *  Author:  Hilton Bristow
 *  Created: Jun 21, 2012
 */

#ifndef FEATURES_HPP_
#define FEATURES_HPP_
#include <vector>
#include <opencv2/core/core.hpp>
#include "types.hpp"

/*! @class Feature interface
 *  @brief Interface for creating and comparing image features
 * IFeatures provides an interface for creating and comparing image features
 */
class IFeatures {
public:
	virtual ~IFeatures() {}
	// get and set methods
	//! retrieve the spatial binning size (1 if not relevant)
	virtual int binsize(void) = 0;
	//! retrieve the number of scales the features are calculated over
	virtual int nscales(void) = 0;
	// public methods
	/*! @brief the vector of scales
	 *
	 * the vector of scales, 1 indicating the native image resolution,
	 * values lower than 1 indicating downsampled images, and values greater
	 * than 1 indicating hallucinated resolutions
	 */
	virtual vectorf scales(void) const = 0;

	/*! @brief a pyramid of features
	 *
	 * features calculated of a number of scales
	 * @param im the input image to calculate features for
	 * @param pyrafeatures an output vector of matrices of features, one matrix for each scale
	 */
	virtual void pyramid(const cv::Mat& im, std::vector<cv::Mat>& pyrafeatures) = 0;

	/*! @brief probability density function
	 *
	 * A custom convolution-type operation for producing a map of probability density functions
	 * where each pixel indicates the likelihood of a positive detection
	 *
	 * @param features the input pyramid of features
	 * @param responses a 2D vector of pdfs, 1st dimension across scale, 2nd dimension across filter
	 */
	virtual void pdf(const std::vector<cv::Mat>& features, vector2DMat& responses) = 0;

	/*! @brief set the convolve engine filters
	 *
	 * In many situations, the filters are static during operation of the detector
	 * so we can take advantage of some optimizations such as changing the memory layout
	 * of the filters, or shifting the filters to the GPU, etc. This function enables
	 * such a facility, and must necessarily be called before pdf()
	 *
	 * @param filters the vector of filters
	 */
	virtual void setFilters(const std::vector<cv::Mat>& filters) = 0;
};

//IFeatures::~IFeatures() {}
#endif /* FEATURES_HPP_ */
