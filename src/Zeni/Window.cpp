/* This file is part of the Zenipex Library (zenilib).
 * Copyright (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * zenilib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * zenilib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with zenilib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <zeni_graphics.h>

#ifdef _MACOSX
#include <SDL_image/SDL_image.h>
#else
#include <SDL/SDL_image.h>
#endif

#ifdef _WINDOWS
#include <SDL/SDL_syswm.h>
#include <Windows.h>
#include <WinUser.h>
#endif

#include <algorithm>
#include <iostream>

#include <Zeni/Define.h>

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <Zeni/Singleton.hxx>

namespace Zeni {

  template class ZENI_GRAPHICS_DLL Singleton<Window>;

  static bool window_mode_lt(const Point2i &lhs, const Point2i &rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
  }

  Window * Window::create() {
    Window * window = 0;

    File_Ops &fo = get_File_Ops();

    const String appdata_path = fo.get_appdata_path();

    const String user_normal = appdata_path + "config/zenilib.xml";
    const String user_backup = user_normal + ".bak";
    const String local_normal = "config/zenilib.xml";
    const String local_backup = local_normal + ".bak";

    static bool last_resort_taken = false;

    try {
      switch(Video::get_video_mode()) {
      case Video::ZENI_VIDEO_ANY:
#ifndef DISABLE_DX9
      case Video::ZENI_VIDEO_DX9:
        Window::set_opengl_flag(false);
        break;
#endif
#ifndef DISABLE_GL
      case Video::ZENI_VIDEO_GL:
        Window::set_opengl_flag(true);
        break;
#endif
      default:
        throw Window_Init_Failure();
      }

      window = new Window;
    }
    catch(Window_Init_Failure &) {
      if(fo.copy_file(user_backup, user_normal) && fo.delete_file(user_backup)) {
        std::cerr << '\'' << user_normal << "' backup restored due to initialization failure.\n";
        Video::preinit_from_file(user_normal);
        get_Window();
      }
      else if(fo.copy_file(local_backup, local_normal) && fo.delete_file(local_backup)) {
        std::cerr << '\'' << local_normal << "' backup restored due to initialization failure.\n";
        Video::preinit_from_file(local_normal);
        get_Window();
      }
      else if(!last_resort_taken) {
        Window::set_failsafe_defaults();

        last_resort_taken = true;

        get_Window();
      }
      else
        throw;
    }

    last_resort_taken = false;

    return window;
  }

  Singleton<Window>::Uninit Window::g_uninit;
  Singleton<Window>::Reinit Window::g_reinit;

  Window::Window()
    :
#if SDL_VERSION_ATLEAST(1,3,0)
    m_window(0),
#else
    m_display_surface(0),
#endif
    m_icon_surface(0)
  {
    if(!g_enabled)
      throw Window_Init_Failure();

    Core::remove_post_reinit(&g_reinit);

    Core &cr = get_Core();

    if(SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)
      throw Window_Init_Failure();

    Core::print_error();

    // Initialize Window Mode Listing
#if SDL_VERSION_ATLEAST(1,3,0)
    const int num_modes = SDL_GetNumDisplayModes();
    for(int i = 0; i != num_modes; ++i) {
      SDL_DisplayMode mode;
      SDL_GetDisplayMode(i, &mode);
      if(m_modes.empty() || m_modes.rbegin()->x != mode.w || m_modes.rbegin()->y != mode.h)
        m_modes.push_back(Point2i(mode.w, mode.h));
    }
#else
    SDL_PixelFormat fmt;
    memset(&fmt, 0, sizeof(SDL_PixelFormat));
    fmt.BitsPerPixel = 32;
    for(SDL_Rect ** mode = SDL_ListModes(&fmt, SDL_FULLSCREEN | SDL_OPENGL); mode && *mode; ++mode)
      m_modes.push_back(Point2i((*mode)->w, (*mode)->h));
#endif

    if(m_modes.empty())
      throw Window_Init_Failure();

    std::sort(m_modes.begin(), m_modes.end(), &window_mode_lt);

    cr.set_screen_saver(false);

    // Initialize SDL + Variables
    const SDL_VideoInfo *VideoInfo = SDL_GetVideoInfo();

#if !SDL_VERSION_ATLEAST(1,3,0)
    set_tt();
    set_icon();
#endif

    const Point2i &max_res = *m_modes.rbegin();

    if(g_screen_size.x < 0)
      g_screen_size.x = max_res.x;
    else if(g_screen_size.x == 0)
      g_screen_size.x = VideoInfo->current_w;
    else if(g_screen_size.x < MINIMUM_SCREEN_WIDTH)
      g_screen_size.x = MINIMUM_SCREEN_WIDTH;
    else if(g_screen_size.x > max_res.x)
      g_screen_size.x = max_res.x;

    if(g_screen_size.y < 0)
      g_screen_size.y = max_res.y;
    else if(g_screen_size.y == 0)
      g_screen_size.y = VideoInfo->current_h;
    else if(g_screen_size.y < MINIMUM_SCREEN_HEIGHT)
      g_screen_size.y = MINIMUM_SCREEN_HEIGHT;
    else if(g_screen_size.y > max_res.y)
      g_screen_size.y = max_res.y;

#if !SDL_VERSION_ATLEAST(1,3,0)
    // Vertical sync can only be specified before Window creation on some platforms
    if(get_opengl_flag())
      SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, Video::get_vertical_sync());
#endif

#ifdef REQUIRE_GL_ES
	  {
		  int err;
#ifdef _WINDOWS
		  err = SDL_GL_LoadLibrary("opengl32.dll");
#else
		  err = SDL_GL_LoadLibrary("libGL.so");
#endif
		  if(err)
        throw Video_Init_Failure();
	  }
#endif

    // Initialize Window
#if SDL_VERSION_ATLEAST(1,3,0)
    m_window = SDL_CreateWindow(get_m_title().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_screen_size.x, g_screen_size.y,
      SDL_WINDOW_OPENGL |
      (g_screen_full ? SDL_WINDOW_FULLSCREEN
                     : ((g_screen_show_frame ? 0u : SDL_WINDOW_BORDERLESS) |
                        (g_screen_resizable ? SDL_WINDOW_RESIZABLE : 0u))));
#else
    m_display_surface = SDL_SetVideoMode(g_screen_size.x, g_screen_size.y, 32,
      SDL_OPENGL |
      (g_screen_full ? SDL_FULLSCREEN
                     : (VideoInfo->wm_available ? ((g_screen_show_frame ? 0 : SDL_NOFRAME) |
                                                   (g_screen_resizable ? SDL_RESIZABLE : 0))
                                                : 0)));
#endif
    Core::assert_no_error();

#if SDL_VERSION_ATLEAST(1,3,0)
    if(!m_window) {
#else
    if(!m_display_surface) {
#endif
      throw Window_Init_Failure();
    }

#if SDL_VERSION_ATLEAST(1,3,0)
    set_tt();
    set_icon();

    SDL_ShowWindow(m_window);
#else
    g_screen_size.x = m_display_surface->w;
    g_screen_size.y = m_display_surface->h;
#endif

    // Force the window to be active and in the foreground, if possible (Windows only)
#ifdef _WINDOWS
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
#if SDL_VERSION_ATLEAST(1,3,0)
    SDL_GetWindowWMInfo(m_window, &wmInfo);
    HWND hWnd = wmInfo.win.window;
#else
    SDL_GetWMInfo(&wmInfo);
    HWND hWnd = wmInfo.window;
#endif

    if(FAILED(SetForegroundWindow(hWnd)))
      SetActiveWindow(hWnd);
#endif

    cr.lend_pre_uninit(&g_uninit);
    cr.lend_post_reinit(&g_reinit);
  }

  Window::~Window() {
#if SDL_VERSION_ATLEAST(1,3,0)
    Core::assert_no_error();
    Core::remove_pre_uninit(&g_uninit);

    if(m_window)
      SDL_DestroyWindow(m_window);
    m_window = 0;

    Core::print_error();

    alert_window_destroyed();
#else
    SDL_FreeSurface(m_display_surface);
    m_display_surface = 0;
#endif

    get_Core().set_screen_saver(true);
  }

  Window & get_Window() {
    return Singleton<Window>::get();
  }

  void Window::preinit_resolution(const Point2i &resolution) {
    g_screen_size = resolution;
  }

  void Window::preinit_full_screen(const bool &full_screen) {
    g_screen_full = full_screen;
  }

  void Window::preinit_show_frame(const bool &show_frame_) {
    g_screen_show_frame = show_frame_;
  }

  void Window::preinit_resizable(const bool &resizable_) {
    g_screen_resizable = resizable_;
  }

  void Window::preinit_from_xml(const XML_Element_c &video) {
    preinit_resolution(Point2i(video["Resolution"]["Width"].to_int(),
                               video["Resolution"]["Height"].to_int()));
    preinit_full_screen(video["Full_Screen"].to_bool());
  }

  void Window::set_failsafe_defaults() {
    g_screen_full = false;
    g_screen_size.x = MINIMUM_SCREEN_WIDTH;
    g_screen_size.y = MINIMUM_SCREEN_HEIGHT;
  }

  const bool & Window::get_opengl_flag() {
    return g_opengl_flag;
  }

  void Window::set_opengl_flag(const bool &on) {
    g_opengl_flag = on;
  }

  void Window::set_enabled(const bool &enabled) {
    g_enabled = enabled;
  }

  void Window::set_tt(const String &title, const String &taskmsg) {
    get_m_title() = title;
    get_m_taskmsg() = taskmsg;

    if(is_initialized())
      get().set_tt();
  }

  void Window::set_title(const String &title) {
    get_m_title() = title;

    if(is_initialized())
      get().set_tt();
  }

  void Window::set_taskmsg(const String &taskmsg) {
    get_m_taskmsg() = taskmsg;

    if(is_initialized())
      get().set_tt();
  }

  bool Window::set_icon(const String &filename) {
    get_m_icon() = filename;

		return !is_initialized() || get().set_icon();
  }

#if SDL_VERSION_ATLEAST(1,3,0)
  void Window::alert_window_destroyed() {
    m_window = 0;
  }
#endif

  void Window::alert_window_resized(const Point2i &resolution) {
    g_screen_size = resolution;
  }

  void Window::set_tt() {
#if SDL_VERSION_ATLEAST(1,3,0)
    if(get_window())
      SDL_SetWindowTitle(get_window(), get_m_title().c_str());
#else
    const SDL_VideoInfo *VideoInfo = SDL_GetVideoInfo();
    if(VideoInfo->wm_available)
      SDL_WM_SetCaption(get_m_title().c_str(), get_m_taskmsg().c_str());
#endif
  }

  bool Window::set_icon() {
#if !SDL_VERSION_ATLEAST(1,3,0)
    const SDL_VideoInfo *VideoInfo = SDL_GetVideoInfo();
    if(!VideoInfo->wm_available)
      return false;
#endif

    m_icon_surface = IMG_Load(get_m_icon().c_str());

    if(!m_icon_surface) {
      std::cerr << "Could not load display window icon\n";
      return false;
    }

#if SDL_VERSION_ATLEAST(1,3,0)
    if(get_window())
      SDL_SetWindowIcon(get_window(), m_icon_surface);
#else
    SDL_WM_SetIcon(m_icon_surface, NULL);
#endif

    return true;
  }

  String & Window::get_m_title() {
    static String title = "zenilib Application";
    return title;
  }

  String & Window::get_m_taskmsg() {
    static String taskmsg = "zenilib Application";
    return taskmsg;
  }

  String & Window::get_m_icon() {
#ifdef _MACOSX
    static String icon = "icons/icon_mac.png";
#else
    static String icon = "icons/icon.gif";
#endif
    return icon;
  }

  bool Window::g_enabled = true;
  Point2i Window::g_screen_size;
  bool Window::g_screen_full = false;
  bool Window::g_screen_show_frame = true;
  bool Window::g_screen_resizable = true;
  bool Window::g_opengl_flag = true;

}
