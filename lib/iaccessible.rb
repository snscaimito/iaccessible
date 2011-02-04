require 'ffi'

module IAccessible

  extend FFI::Library

  ffi_lib File.dirname(__FILE__) + '../../ext/iasupport/Release/iasupport.dll', 'user32', 'oleacc'
  ffi_convention :stdcall

  attach_function :find_window, :FindWindowA,
                  [:pointer, :pointer], :long

  # oleacc
  attach_function :get_role_text, :GetRoleTextA,
                  [:int32, :pointer, :uint32], :uint32

  # iasupport
  attach_function :get_accChildCount, :get_accChildCount,
                  [:long], :int
  attach_function :get_accRole, :get_accRole,
                  [:long, :long], :long
  attach_function :get_accName, :get_accName,
                  [:long, :long, :pointer, :int], :int
  attach_function :is_accessible, :is_accessible,
                  [:long, :long], :bool

end
