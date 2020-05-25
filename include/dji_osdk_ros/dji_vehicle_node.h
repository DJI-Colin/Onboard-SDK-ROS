/** @file dji_vehicle_node.hpp
 *  @version 4.0
 *  @date May 2020
 *
 *  @brief main node of osdk ros 4.0.All services and topics are inited here.
 *
 *  @Copyright (c) 2020 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __DJI_VEHICLE_NODE_HH__
#define __DJI_VEHICLE_NODE_HH__

// Header include
#include <ros/ros.h>
#include <dji_vehicle.hpp>

#include <dji_osdk_ros/vehicle_wrapper.h>
#include <dji_osdk_ros/common_type.h>

#include <memory>
#include <string>

//! ROS standard msgs
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/TimeReference.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <nmea_msgs/Sentence.h>

/*! services */
#include <dji_osdk_ros/FlightTaskControl.h>
#include <dji_osdk_ros/GimbalAction.h>
#include <dji_osdk_ros/CameraEV.h>
#include <dji_osdk_ros/CameraShutterSpeed.h>
#include <dji_osdk_ros/CameraAperture.h>
#include <dji_osdk_ros/CameraISO.h>
#include <dji_osdk_ros/CameraFocusPoint.h>
#include <dji_osdk_ros/CameraTapZoomPoint.h>
#include <dji_osdk_ros/CameraZoomCtrl.h>
#include <dji_osdk_ros/CameraStartShootBurstPhoto.h>
#include <dji_osdk_ros/CameraStartShootAEBPhoto.h>
#include <dji_osdk_ros/CameraStartShootSinglePhoto.h>
#include <dji_osdk_ros/CameraStartShootIntervalPhoto.h>
#include <dji_osdk_ros/CameraStopShootPhoto.h>
#include <dji_osdk_ros/CameraRecordVideoAction.h>
#include <dji_osdk_ros/MFIO.h>
#include <dji_osdk_ros/SetGoHomeAltitude.h>
#include <dji_osdk_ros/SetNewHomePoint.h>
#include <dji_osdk_ros/SetLocalPosRef.h>
#include <dji_osdk_ros/AvoidEnable.h>
#ifdef ADVANCED_SENSING
#include <dji_osdk_ros/AdvancedSensing.h>
#include <dji_osdk_ros/CameraData.h>

/*! msgs */
#include <dji_osdk_ros/Gimbal.h>
#include <dji_osdk_ros/MobileData.h>
#include <dji_osdk_ros/PayloadData.h>
#include <dji_osdk_ros/FlightAnomaly.h>
#include <dji_osdk_ros/VOPosition.h>
#include <dji_osdk_ros/FCTimeInUTC.h>
#include <dji_osdk_ros/GPSUTC.h>
#endif


#define C_EARTH (double)6378137.0
#define C_PI (double)3.141592653589793
#define DEG2RAD(DEG) ((DEG) * ((C_PI) / (180.0)))
#define RAD2DEG(RAD) ((RAD) * (180.0) / (C_PI))

// Declaration
namespace dji_osdk_ros
{
  using namespace DJI::OSDK;
  using namespace Telemetry;

  class VehicleNode
  {
    public:
      VehicleNode();
      VehicleNode(int test);

      ~VehicleNode();

      bool subscribeGimbalData();
      bool unSubScribeGimbalData();
      bool initCameraModule();
      void initService();
      bool initTopic();
      void publishTopic();
      bool initDataSubscribeFromFC();
      bool cleanUpSubscribeFromFC();
#ifdef ADVANCED_SENSING
      dji_osdk_ros::CameraData getCameraData();
#endif
    protected:
      /*! services */
      ros::ServiceServer task_control_server_;
      ros::ServiceServer gimbal_control_server_;
      /*! for camera*/
      ros::ServiceServer camera_control_set_EV_server_;
      ros::ServiceServer camera_control_set_shutter_speed_server_;
      ros::ServiceServer camera_control_set_aperture_server_;
      ros::ServiceServer camera_control_set_ISO_server_;
      ros::ServiceServer camera_control_set_focus_point_server_;
      ros::ServiceServer camera_control_set_tap_zoom_point_server_;
      ros::ServiceServer camera_control_zoom_ctrl_server_;
      ros::ServiceServer camera_control_start_shoot_single_photo_server_;
      ros::ServiceServer camera_control_start_shoot_burst_photo_server_;
      ros::ServiceServer camera_control_start_shoot_AEB_photo_server_;
      ros::ServiceServer camera_control_start_shoot_interval_photo_server_;
      ros::ServiceServer camera_control_stop_shoot_photo_server_;
      ros::ServiceServer camera_control_record_video_action_server_;
      /*! for mfio*/
      ros::ServiceServer mfio_control_server_;
      /*! for flight control*/
      ros::ServiceServer set_home_altitude_server_;
      ros::ServiceServer set_current_point_as_home_server_;
      ros::ServiceServer set_local_pos_reference_server_;
      ros::ServiceServer avoid_enable_server_;
    /*! for advanced sensing*/
#ifdef ADVANCED_SENSING
      ros::ServiceServer advanced_sensing_server_;
      ros::Publisher advanced_sensing_pub_;
#endif

      /*! publishers */
      //! telemetry data publisher
      ros::Publisher attitude_publisher_;
      ros::Publisher angularRate_publisher_;
      ros::Publisher acceleration_publisher_;
      ros::Publisher battery_state_publisher_;
      ros::Publisher trigger_publisher_;
      ros::Publisher imu_publisher_;
      ros::Publisher flight_status_publisher_;
      ros::Publisher gps_health_publisher_;
      ros::Publisher gps_position_publisher_;
      ros::Publisher vo_position_publisher_;
      ros::Publisher height_publisher_;
      ros::Publisher velocity_publisher_;
      ros::Publisher from_mobile_data_publisher_;
      ros::Publisher from_payload_data_publisher_;
      ros::Publisher gimbal_angle_publisher_;
      ros::Publisher displaymode_publisher_;
      ros::Publisher rc_publisher_;
      ros::Publisher rc_connection_status_publisher_;
      ros::Publisher rtk_position_publisher_;
      ros::Publisher rtk_velocity_publisher_;
      ros::Publisher rtk_yaw_publisher_;
      ros::Publisher rtk_position_info_publisher_;
      ros::Publisher rtk_yaw_info_publisher_;
      ros::Publisher rtk_connection_status_publisher_;
      ros::Publisher flight_anomaly_publisher_;
      //! Local Position Publisher (Publishes local position in ENU frame)
      ros::Publisher local_position_publisher_;
      ros::Publisher local_frame_ref_publisher_;
      ros::Publisher time_sync_nmea_publisher_;
      ros::Publisher time_sync_gps_utc_publisher_;
      ros::Publisher time_sync_fc_utc_publisher_;
      ros::Publisher time_sync_pps_source_publisher_;

    protected:
      bool taskCtrlCallback(FlightTaskControl::Request& request, FlightTaskControl::Response& response);
      /*! for gimbal */
      bool gimbalCtrlCallback(GimbalAction::Request& request, GimbalAction::Response& response);
      /*! for camera*/
      bool cameraSetEVCallback(CameraEV::Request& request, CameraEV::Response& response);
      bool cameraSetShutterSpeedCallback(CameraShutterSpeed::Request& request, CameraShutterSpeed::Response& response);
      bool cameraSetApertureCallback(CameraAperture::Request& request, CameraAperture::Response& response);
      bool cameraSetISOCallback(CameraISO::Request& request, CameraISO::Response& response);
      bool cameraSetFocusPointCallback(CameraFocusPoint::Request& request, CameraFocusPoint::Response& response);
      bool cameraSetTapZoomPointCallback(CameraTapZoomPoint::Request& request, CameraTapZoomPoint::Response& response);
      bool cameraZoomCtrlCallback(CameraZoomCtrl::Request& request, CameraZoomCtrl::Response& response);
      bool cameraStartShootSinglePhotoCallback(CameraStartShootSinglePhoto::Request& request, CameraStartShootSinglePhoto::Response& response);
      bool cameraStartShootAEBPhotoCallback(CameraStartShootAEBPhoto::Request& request, CameraStartShootAEBPhoto::Response& response);
      bool cameraStartShootBurstPhotoCallback(CameraStartShootBurstPhoto::Request& request, CameraStartShootBurstPhoto::Response& response);
      bool cameraStartShootIntervalPhotoCallback(CameraStartShootIntervalPhoto::Request& request, CameraStartShootIntervalPhoto::Response& response);
      bool cameraStopShootPhotoCallback(CameraStopShootPhoto::Request& request, CameraStopShootPhoto::Response& response);
      bool cameraRecordVideoActionCallback(CameraRecordVideoAction::Request& request, CameraRecordVideoAction::Response& response);

      bool mfioCtrlCallback(MFIO::Request& request, MFIO::Response& response);

      bool setGoHomeAltitudeCallback(SetGoHomeAltitude::Request& request, SetGoHomeAltitude::Response& response);
      bool setHomeCallback(SetNewHomePoint::Request& request, SetNewHomePoint::Response& response);
      bool setLocalPosRefCallback(dji_osdk_ros::SetLocalPosRef::Request &request,
                                             dji_osdk_ros::SetLocalPosRef::Response &response);
      bool setAvoidCallback(AvoidEnable::Request& request, AvoidEnable::Response& response);

#ifdef ADVANCED_SENSING
      bool advancedSensingCallback(AdvancedSensing::Request& request, AdvancedSensing::Response& response);
      void publishAdvancedSeningData();
#endif

      bool initSubscribe();

    private:
      ros::NodeHandle nh_;
      VehicleWrapper* ptr_wrapper_;
      TelemetryType telemetry_from_fc_;

      int           app_id_;
      int           app_version_;
      int           baud_rate_;
      double        gravity_const_;
      std::string   enc_key_;
      std::string   device_acm_;
      std::string   device_;
      std::string   sample_case_;
      std::string   drone_version_;
      std::string   app_bundle_id_; // reserved
      bool          user_select_broadcast_;
      bool          align_time_with_FC_;

      AlignStatus curr_align_state_;
      ros::Time   base_time_;
      double      local_pos_ref_latitude_, local_pos_ref_longitude_, local_pos_ref_altitude_;
      double      current_gps_latitude_, current_gps_longitude_, current_gps_altitude_;
      bool        local_pos_ref_set_;
      int         current_gps_health_;
      const       tf::Matrix3x3 R_FLU2FRD_;
      const       tf::Matrix3x3 R_ENU2NED_;
      bool        rtk_support_;

#ifdef ADVANCED_SENSING
      bool is_h264_;
#endif
    //! data broadcast callback
    void dataBroadcastCallback();
    void fromMobileDataCallback(RecvContainer recvFrame);

    void fromPayloadDataCallback(RecvContainer recvFrame);

    static void NMEACallback(Vehicle* vehiclePtr,
                             RecvContainer recvFrame,
                             UserData userData);

    static void GPSUTCTimeCallback(Vehicle *vehiclePtr,
                                   RecvContainer recvFrame,
                                   UserData userData);


    static void FCTimeInUTCCallback(Vehicle* vehiclePtr,
                                    RecvContainer recvFrame,
                                    UserData userData);

    static void PPSSourceCallback(Vehicle* vehiclePtr,
                                  RecvContainer recvFrame,
                                  UserData userData);
    static void SDKfromMobileDataCallback(Vehicle*            vehicle,
                                          RecvContainer       recvFrame,
                                          DJI::OSDK::UserData userData);

    static void SDKfromPayloadDataCallback(Vehicle *vehicle,
                                           RecvContainer recvFrame,
                                           DJI::OSDK::UserData userData);

    static void SDKBroadcastCallback(Vehicle*            vehicle,
                                     RecvContainer       recvFrame,
                                     DJI::OSDK::UserData userData);

    static void publish5HzData(Vehicle*            vehicle,
                               RecvContainer       recvFrame,
                               DJI::OSDK::UserData userData);

    static void publish50HzData(Vehicle*            vehicle,
                                RecvContainer       recvFrame,
                                DJI::OSDK::UserData userData);

    static void publish100HzData(Vehicle*            vehicle,
                                 RecvContainer       recvFrame,
                                 DJI::OSDK::UserData userData);

    static void publish400HzData(Vehicle*            vehicle,
                                 RecvContainer       recvFrame,
                                 DJI::OSDK::UserData userData);

public:
    void gpsConvertENU(double &ENU_x, double &ENU_y,
                       double gps_t_lon, double gps_t_lat,
                       double gps_r_lon, double gps_r_lat);
    void alignRosTimeWithFlightController(ros::Time now_time, uint32_t tick);
  };
}
#endif // __DJI_VEHICLE_NODE_HH__

