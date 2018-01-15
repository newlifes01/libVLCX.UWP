/*****************************************************************************
* StructuresCX.cpp: LibVLC++ structures
*****************************************************************************
* Copyright � 2014 the VideoLAN team
*
* Authors: Hugo Beauz�e-Luyssen <hugo@beauzee.fr>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2.1 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*****************************************************************************/

#include "StructuresCX.hpp"
#include "Helpers.h"

namespace libVLCX
{
    Platform::String^ ModuleDescription::name()
    {
        return m_name;
    }
    Platform::String^ ModuleDescription::shortname()
    {
        return m_shortname;
    }
    Platform::String^ ModuleDescription::longname()
    {
        return m_longname;
    }
    Platform::String^ ModuleDescription::help()
    {
        return m_help;
    }

    ModuleDescription::ModuleDescription(const VLC::ModuleDescription& desc)
    {
        m_name = ToPlatformString(desc.name().c_str());
        m_shortname = ToPlatformString(desc.shortname().c_str());
        m_longname = ToPlatformString(desc.longname().c_str());
        m_help = ToPlatformString(desc.help().c_str());
    }


    uint32_t MediaTrack::codec()
    {
        return m_codec;
    }
    uint32_t MediaTrack::originalFourCC()
    {
        return m_originalFourcc;
    }
    int32_t MediaTrack::id()
    {
        return m_id;
    }
    TrackType MediaTrack::type()
    {
        return m_type;
    }
    int32_t MediaTrack::profile()
    {
        return m_profile;
    }
    int32_t MediaTrack::level()
    {
        return m_level;
    }
    uint32_t MediaTrack::bitrate()
    {
        return m_bitrate;
    }
    Platform::String^ MediaTrack::language()
    {
        return m_language;
    }
    Platform::String^ MediaTrack::description()
    {
        return m_description;
    }
    // Audio specific
    uint32_t MediaTrack::channels()
    {
        return m_channels;
    }
    uint32_t MediaTrack::rate()
    {
        return m_rate;
    }
    // Video specific
    uint32_t MediaTrack::height()
    {
        return m_height;
    }
    uint32_t MediaTrack::width()
    {
        return m_width;
    }
    uint32_t MediaTrack::sarNum()
    {
        return m_sarNum;
    }
    uint32_t MediaTrack::sarDen()
    {
        return m_sarDen;
    }
    uint32_t MediaTrack::fpsNum()
    {
        return m_fpsNum;
    }
    uint32_t MediaTrack::fpsDen()
    {
        return m_fpsDen;
    }
    Orientation MediaTrack::orientation()
    {
        return m_orientation;
    }
    Projection MediaTrack::projection()
    {
        return m_projection;
    }

    // Subtitles specific
    Platform::String^ MediaTrack::encoding()
    {
        return m_encoding;
    }

    MediaTrack::MediaTrack(const VLC::MediaTrack& track)
    {
        m_codec = track.codec();
        m_originalFourcc = track.originalFourCC();
        m_id = track.id();
        m_type = (TrackType) track.type();
        m_profile = track.profile();
        m_level = track.level();
        m_bitrate = track.bitrate();
        m_language = ToPlatformString(track.language().c_str());
        m_description = ToPlatformString(track.description().c_str());
        m_channels = track.channels();
        m_rate = track.rate();
        m_height = track.height();
        m_width = track.width();
        m_sarNum = track.sarNum();
        m_sarDen = track.sarDen();
        m_fpsNum = track.fpsNum();
        m_fpsDen = track.fpsDen();
        m_orientation = (Orientation) track.orientation();
        m_projection = (Projection) track.projection();
        m_encoding = ToPlatformString(track.encoding().c_str());
    }



    Platform::String^ AudioOutputDescription::name()
    {
        return m_name;
    }
    Platform::String^ AudioOutputDescription::description()
    {
        return m_description;
    }

    AudioOutputDescription::AudioOutputDescription(const VLC::AudioOutputDescription& desc)
    {
        m_name = ToPlatformString(desc.name().c_str());
        m_description = ToPlatformString(desc.description().c_str());
    }

    Platform::String^ AudioOutputDeviceDescription::device()
    {
        return m_device;
    }
    Platform::String^ AudioOutputDeviceDescription::description()
    {
        return m_description;
    }
    AudioOutputDeviceDescription::AudioOutputDeviceDescription(const VLC::AudioOutputDeviceDescription& desc)
    {
        m_device = ToPlatformString(desc.device().c_str());
        m_description = ToPlatformString(desc.description().c_str());
    }
    // TrackDescription
    int TrackDescription::id()
    {
         return m_id;
    }

    Platform::String^ TrackDescription::name()
    {
         return m_name;
    }

    TrackDescription::TrackDescription(const VLC::TrackDescription& desc)
    {
         m_id = desc.id();
         m_name = ToPlatformString(desc.name().c_str());
    }

    // TitleDescription
    int64_t TitleDescription::duration()
    {
         return m_duration;
    }

    int TitleDescription::id()
    {
         return m_id;
    }

    Platform::String^ TitleDescription::name()
    {
         return m_name;
    }

    bool TitleDescription::isMenu()
    {
         return m_menu;
    }

    TitleDescription::TitleDescription(const VLC::TitleDescription& desc)
    {
         m_menu = desc.isMenu();
         m_duration = desc.duration();
         m_name = ToPlatformString(desc.name().c_str());
    }

    // Chapter decription
    int ChapterDescription::id()
    {
         return m_id;
    }

    int64_t ChapterDescription::startTime()
    {
         return m_startTime;
    }

    int64_t ChapterDescription::duration()
    {
         return m_duration;
    }

    Platform::String^ ChapterDescription::name()
    {
         return m_name;
    }

    ChapterDescription::ChapterDescription(const VLC::ChapterDescription& desc)
    {
         m_duration = desc.duration();
         m_startTime = desc.starttime();
         m_name = ToPlatformString(desc.name().c_str());
    }

    MediaSlave::MediaSlave(const VLC::MediaSlave& slave) :
        m_obj(slave)
    {
        m_uri = ToPlatformString(m_obj.uri());
    }

    SlaveType MediaSlave::type()
    {
        return (SlaveType)m_obj.type();
    }

    unsigned MediaSlave::priority()
    {
        return m_obj.priority();
    }

    Platform::String^ MediaSlave::uri()
    {
        return m_uri;
    }

    VideoViewpoint::VideoViewpoint(float yaw, float pitch, float roll, float fieldOfView)
        : m_viewpoint(yaw, pitch, roll, fieldOfView)
    {
    }

    float VideoViewpoint::yaw()
    {
        return m_viewpoint.yaw();
    }

    float VideoViewpoint::pitch()
    {
        return m_viewpoint.pitch();
    }

    float VideoViewpoint::roll()
    {
        return m_viewpoint.roll();
    }

    float VideoViewpoint::field_of_view()
    {
        return m_viewpoint.field_of_view();
    }

    Platform::String^ MediaDiscovererDescription::name()
    {
        return m_name;
    }

    Platform::String^ MediaDiscovererDescription::longName()
    {
        return m_longName;
    }

    MediaDiscovererCategory MediaDiscovererDescription::category()
    {
        return m_category;
    }

    MediaDiscovererDescription::MediaDiscovererDescription(const VLC::MediaDiscoverer::Description& desc)
        : m_name(ToPlatformString(desc.name().c_str()))
        , m_longName(ToPlatformString(desc.longName().c_str()))
        , m_category(static_cast<MediaDiscovererCategory>(desc.category()))
    {
    }
}
