require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

describe "Iaccessible" do
  it "fails" do
    hwnd = IAccessible.find_window(nil, "MainFormWindow")

    childs = IAccessible.get_accChildCount(hwnd)

    (0..childs).each do |child|
      role_id = IAccessible.get_accRole(hwnd, child)

      name_len = IAccessible.get_accName(hwnd, child, nil, 0) + 1
      name_ptr = FFI::MemoryPointer.new :char, name_len
      IAccessible.get_accName(hwnd, child, name_ptr, name_len)
      name = name_ptr.read_string

      role_name_ptr = FFI::MemoryPointer.new :char, 255
      IAccessible.get_role_text(role_id, role_name_ptr, 255)
      role_name = role_name_ptr.read_string

      puts "Child #{child} with name #{name} has role id #{role_id} which is #{role_name}"

      puts "it is accessible" if (IAccessible.is_accessible(hwnd, child))

    end
  end
end
