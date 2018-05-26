Explore how to implement both variant and tuple using the 
multiple-inheritance of leaf classes technique described
here:
  http://mitchnull.blogspot.com/2012/06/c11-tuple-implementation-details-part-1.html
However, instead of a leaf class being a pair of (non-type Index, typename Value)
they are a pair of (typename Index, typename Value).  In addition, the essential
difference between the leaf class for a tuple and the leaf class for the variant
is that the Value is actually stored in the leaf for the tuple whereas for the
variant, only a CTOR function taking a void* from the base class is defined.

I've no idea how useful it may be, but it seemed like it could reuse the concept
of leaf-classes and multiple inheritance and I just thought that might be useful.
