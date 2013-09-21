#ifndef __JZSYS_H__
#define __JZSYS_H__

#if defined(_UCOS_)
# define MPALLOC(size)     av_malloc(size)
# define MPFREE(p)         av_free(p)
#else
# define MPALLOC(size)     jz4740_alloc_frame(0, size)
# define MPFREE(p)         
#endif

#if defined(_UCOS_)
#define get_phy_addr(vaddr) (unsigned int)(((unsigned int)(vaddr)) & 0x1FFFFFFF)
#else
#define get_phy_addr(vaddr) (unsigned int)(((unsigned int)(vaddr) - (unsigned int)frame_buffer) + phy_fb)
#endif

#define get_vaddr(paddr) (unsigned int)(((unsigned int)(paddr) - (unsigned int)phy_fb) + (unsigned int)frame_buffer)

/*aux get phy addr*/
#if defined(_UCOS_)
#define get_phy_addr_aux(vaddr) (unsigned int)(((unsigned int)(vaddr)) & 0x1FFFFFFF)
#elif defined(_RTL_SIM_)
#define get_phy_addr_aux(vaddr) (unsigned int)((((unsigned int)(vaddr)) & 0x0FFFFFFF) | 0x20000000)
#else
#define get_phy_addr_aux(vaddr) (vaddr)
#endif

#define get_k0_addr(addr) (get_phy_addr((addr))+0x80000000)

/*main-cpu push addr for aux*/
#if defined(_UCOS_) || defined(_RTL_SIM_)
# define tran_addr_for_aux(vaddr) (vaddr)
#endif


#define get_p1_phy_addr(vaddr) (unsigned int)(((unsigned int)(vaddr)) & 0x1FFFFFFF)
#endif /*__JZSYS_H__*/
