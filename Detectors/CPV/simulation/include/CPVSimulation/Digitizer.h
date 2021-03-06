// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef ALICEO2_CPV_DIGITIZER_H
#define ALICEO2_CPV_DIGITIZER_H

#include "DataFormatsCPV/Digit.h"
#include "CPVBase/Geometry.h"
#include "CPVCalib/CalibParams.h"
#include "CPVBase/Hit.h"
#include "SimulationDataFormat/MCCompLabel.h"
#include "SimulationDataFormat/MCTruthContainer.h"

namespace o2
{
namespace cpv
{
class Digitizer : public TObject
{
 public:
  Digitizer() = default;
  ~Digitizer() override = default;
  Digitizer(const Digitizer&) = delete;
  Digitizer& operator=(const Digitizer&) = delete;

  void init();
  void finish();

  /// Steer conversion of hits to digits
  void process(const std::vector<Hit>* hitsBg, const std::vector<Hit>* hitsS, std::vector<Digit>& digits, o2::dataformats::MCTruthContainer<o2::MCCompLabel>& labels);

  void setEventTime(double t);
  double getEventTime() const { return mEventTime; }

  void setCurrEvID(int v);
  int getCurrEvID() const { return mCurrEvID; }

 protected:
  float simulateNoise();
  float uncalibrate(float e, int absId);

 private:
  const CalibParams* mCalibParams = nullptr; //! Calibration coefficients
  double mEventTime = 0;                     ///< global event time
  uint mROFrameMin = 0;                      ///< lowest RO frame of current digits
  uint mROFrameMax = 0;                      ///< highest RO frame of current digits
  int mCurrSrcID = 0;                        ///< current MC source from the manager
  int mCurrEvID = 0;                         ///< current event ID from the manager

  ClassDefOverride(Digitizer, 1);
};
} // namespace cpv
} // namespace o2

#endif /* ALICEO2_CPV_DIGITIZER_H */
